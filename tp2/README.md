# Trabajo Práctico 2: Split-Apply-Combine
</br>

## Taller de programación - Veiga - 2021 2C

### Vázquez Lareu, Román. 100815


</br>
El presente trabajo implementa un programa que recibe un dataset en binario y una tareas a realizar por stdin. Al finalizar imprime el resultado de las tareas en el orden en que fueron pedidas.


# Diseño (12/10/2021)
</br>

El trabajo práctico se dividió en bloques, donde las responsabilidades se van pasando de arriba hacia abajo. Al iniciar el programa, este crea un *binaryReader* encargado de leer el dataset y devolver valor con el formato correcto, y un *TaskManager*. Al construirse, este ultimo crea un *taskContainer* por cada tarea. A su vez, de acuerdo a las *partition rows* indicadas en la tarea, creará tantos *Task* como sean necesarios para completar la tarea.
</br></br>
Por ejemplo, si la tarea indica que se lea de la fila 0 a 5 y con 2 *partition rows*, el *taskContainer* tendrá 3 *task*: uno que resolverá la operación indicada con las filas 0-1, otro 2-3 y el último con la fila 4. Los resultados parciales serán ubicados en un vector perteneciente a *taskContainer*. Al vaciarse la lista de *tasks* y al llenarse el vector con los resultados parciales, el *taskContainer* finalmente realiza la operación con los resultados parciales.
</br></br>
De esta manera se extraen *taskContainers* de la cola protegida del *taskManager*, y a su vez desencolarán *task* de la cola protegida del *taskContainer*, unicamente cuando es vaciada esta última se procederá a desencolar un nuevo *taskContainer*.

![](/classDiagram.png)


# Versión Reentrega (26/10/2021)

## Diseño
</br>

Al iniciar el programa, se crea un *binaryReader* encargado de leer el dataset y devolver lo leido en el formato correcto. Además se crea un *TaskManager*, encargado de crear las particiones y cargarlas en una *blocking queue*. Cada partición se identifica con su tarea correspondiente mediante un ID. Los *Worker Threads* se encargan de desencolar la partición, realizar la lectura de la sección correspondiente en el dataset (zona crítica) y guardar el *PartialResult* en un objeto compartido (zona crítica). Finalmente el hilo principal *joinea* a los *workers* y calcula los valores finales de las tareas en base a los resultados parciales.

* *TaskManager*: crea cola con particiones y obtiene resultados finales en base a parciales
* *Task*: partición, varias corresponden a una misma tarea. Se identifican por ID con el número de tarea.
* *BinaryReader*: permite a las *Task* leer del dataset en forma concurrente
* *Utils*: herramienta para las *task* para resolver los calculos a realizar
* *PartialResults*: contenedor con resultador parciales
* *ProtectedQueue*: cola con particiones *thread safe*
* *Thread*: clase wrapper de `std::thread`
* *Worker*: extiende a *Thread*, implementa la lógica (resolución de partición) en el método `run`.

![](/classDiagram2.png)

Las zonas críticas a prestar atención en *mutithreading* son 3:
</br>
1. Cola de particiones: implementada como *thread safe*. No fue necesario poner tope, en la cola únicamente se cargan las particiones, luego cada hilo en base a la partición lee del dataset y carga en memoria. Se implementó de tal manera que únicamente se hace *pop* si es posible. De no haber más particiones en la cola, el *thread* puede aguardar a una notificación por parte del hilo principal de que se ha cargado una partición en la cola o será *joineado* por el hilo de ejecución principal al finalizar la resolución de las tareas.
2. Acceso a lectura de dataset: al usar punteros para moverse dentro del dataset, esta acción también debe ser realizada con un *mutex*.
3. Guardado de resultados parciales en objeto compartido -> monitor
</br>

## Issues
1. Verificar argc
  ```
    if (argc != 4) {
        printf("invalid amount argc, %d received", argc);
        return 1;
    }
  ```
2. Crear wrapper de Thread: Worker extiende de Thread e implementa la tarea a realizar en `run()` 


```
   class Thread {
    private:
        std::thread thread;

    public:
        Thread();

        void start();

        void join();

        virtual void run() = 0;
```

```
    //WORKER
    virtual void run() override {
        while (!this->taskManager->tasks_queue_is_empty()) {
            Task task = this->taskManager->get_task();
            task.solve(this->binaryReader);
            std::tuple<int, uint16_t, int, std::string> r = task.get_result();
            this->results->push_back(r);
        } 
    }
```


3. Modificar *TaskContainer*, no es necesario: se elimina y el *TaskManager* directamente carga las particiones en una cola. Los *Workers* extraen, resuelven y ponen resultado parcial en objeto compartido. Finalmente el hilo principal obtiene resultados definitivos a partir de parciales.
4. `std::stringstream` utilizada para realizar un *split_line* al momento de leer las tareas a realizar por *stdin*
```
std::vector<std::string> TaskManager::split_line(std::string line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token.c_str());
    }
    return tokens;
}
```

5. Crear objeto que encapsule partición (**Sin Implementar**)
6. Sacar comportamiento de la clase del constructor de *TaskManager*
7. Pasar nombre de dataset por referencia y catchear excepciones
```
BinaryReader::BinaryReader(std::string &name) {
    try {
        this->file.open(name, std::ios::binary);
        
        if (!this->file.is_open()) {
                throw std::invalid_argument("error in open");
        }
    }
    catch(std::invalid_argument &e) {
        std::cout << e.what();
    }
```
8. En constructor por movimiento, evaluar el caso en el que `this == &other`
9. Reemplazar el ajuste por endiannes manuel por `ntohs`
```
    uint16_t value;
    this->file.read(reinterpret_cast<char*>(&value), sizeof(value)); 
    value = ntohs(value);
```

10. No cerrar el dataset en el destructor de BinaryReader, innecesario ya que es de tipo `std::ifstream` que es RAII
11. Implementar de forma segura para *multithreading* la lectura del dataset

```
std::vector<uint16_t> BinaryReader::read_range(int column,
                                            int start_range,
                                                int end_range,
                                                 int cols) {
    std::vector<uint16_t> read_values;
    std::lock_guard<std::mutex> lock(mutex);
    for (int i = 0; i < end_range - start_range; i++) {
        this->file.seekg((column) * 2 + ((cols * 2) * (start_range + i)));
        read_values.push_back(this->read());
    }
    return read_values;
}
```
12. Refactorizar resolucíon de tarea: se implementó el objeto PartialResult

```
class PartialResults {
    private:
        std::vector<std::tuple<int, uint16_t, int, std::string>> results;
        std::mutex mutex;
    public:
        void push_back(std::tuple<int, uint16_t, int, std::string> result);
        std::tuple<int, uint16_t, int, std::string>&  at(size_t i); 
        unsigned int size();
};
```
13. Misma idea que 12 pero para imprimir por pantalla
14. Misma idea que 12 pero para *TaskContainer*, se eliminó esta clase.
15. Realización de constructores por movimiento: implementados pero comentados

# Re-Reentrega (09/11/2021)

1. reservar espacio en vector de threads, construyendo in-place
2. Pasar objetos a hilos por referencia y no por puntero crudo. Usar initializer list para argumentos
3. Reordenar .h de *Worker*
4. Cumplir con la consigna, colocando tokens al final de la cola para que retiren los *workers* y terminen su ejecución. Modifica la condición del while, el hilo espera si la cola está vacía en vez de salir.
5. Constructores por asignacion/movimiento para *Task*, *BinaryReader*. Además del uso de *std::move* y *std:.ref*
6. Crear task por movimiento al obtener de la cola, para la devolución si bien es por copia se da *copy elision*
7. Mapa de funciones para la resolución de la suma, promedio, mínimo y máximo sin preguntar por tipo
8. Verificar this == &other en constructores por movimiento/asignación.
9. Método *read* de *BinaryReader* es privado
10. casteo de referencia a string de operación en initializer list
11. *TaskManager* recibe una cola vacía y la devuelve llena de particiones mediante un método público. Se elimina comportamiento de constructor y desacopla la queue del *TaskManager*
12. Método split_line de *BinaryReader* es const y la linea se pasa por movimiento
13. Mapa de funciones para *TaskManager::solve()* (resuelto con ternary operator, no con mapa)
14. Método print_results de *TaskManager* ahora es privado
15. Mapa de strings y otras estructuras pesadas ahora se pasan por referencia

