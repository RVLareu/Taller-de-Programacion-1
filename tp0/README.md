# Trabajo Práctico 0

* Vázquez Lareu, Román
* 100815
* https://github.com/RVLareu/tp0.git

## Paso 0 - Entorno de trabajo

1. <br> ![Captura con y sin Valgrind](/images/valgrind.png)
2. *Valgrind* sirve para debuggear, ayudando a detectar problemas en el manejo de memoria y de threading. La opción mas importante es la de seleccionar el tool: uno posible y a su vez el más común que viene por default es la de *memcheck*, que indica que toda la memoria allocada sea debidamente liberada. Según la documentación, otro toolname popular es *cachegrind*, que indica todo lo referido a la memoria cache en la ejecución del programa (referencias y misses tanto de datos como de instrucciones). En cuanto a otras opciones posibles son *-q* (solo imprime errores de mensaje), *-v* (imprime información adicional), *--vgdb=yes* (permite debuggear utilizando GDB), entre otras.
3. *sizeof()* devuelve el tamaño de un tipo de dato o expresión en bytes. el *sizeof(char)* devuelve 1 (byte) y el *sizeof(int)* devuelve 4 (bytes), aunque en el caso del *int* podría variar dependiendo de la arquitectura y del compilador.
4. el *sizeof()* de un struct puede no ser igual a la suma de los *sizeof()* de cada uno de sus elementos. Cuando se hace el *sizeof()* del struct en su totalidad, se tiene en cuenta el padding, por lo que si el struct tiene un elemento *char* y uno *int*, el *sizeof()* del struct será 8 (4 del *int*, 1 del *char* y 3 del padding del *char*). Ahora bien, al hacer la suma por separada el valor será 5 (4 del *int* y 1 del *char*) ya que no se tiene en cuenta el padding. En el caso de que el struct se encuentre formado únicamente por elementos de tipo *int*,o que el struct tenga el atribute *packed* no se daría esta diferencia (entre otros ejemplos).
5. STDIN corresponde a la entrada estándar y es de lo que se alimentará el programa/comando, STDOUT y STDERR son de salida, el primero para la salida estándar del programa por la shell y el segundo en caso de error. El pipe concatena la salida estandar de uno con la entrada estandar de otro, de esta manera la salida de un proceso será el input del de la derecha del pipe. Con > se puede redireccionar la salida a, por ejemplo, un archivo de texto. Con < se puede indicar que el input provenga de un archivo en particular. Cada proceso tendrá sus propios STDIN, STDOUT y STDERR.


## Paso 1 - Errores de generación y normas de programación

1. <br> ![Captura errores estilo paso1](/images/errorEstiloPaso1.png)


Deberia haber un espacio entre el *while* y el paréntesis que abre la expresión a evaluar.
|Incorrecto | Correcto|
|------------ | -------------|
|<pre lang="C"> while(state != STATE_FINISHED); </pre>|<pre lang="C"> while (state != STATE_FINISHED);</pre>|

El espaciado dentro de los paréntesis debería ser consistente a izquierda y a derecha. Además deberia haber a lo sumo un espacio a cada lado. En este caso hay dos a iquierda y ninguno a derecha. Los operadores siempre van rodeados de espacios. 
|Incorrecto | Correcto|
|------------ | -------------|
|<pre lang="C"> if (  c == EOF) { </pre> | <pre lang="C"> if (c == EOF) { </pre>|

El *else* debería haber estado en la misma linea que el } que cierra el bloque previo. Además, si tiene una llave a derecha o izquierda debería estar la correspondiente del lado opuesto.
|Incorrecto | Correcto|
|------------ | -------------|
|<pre lang="C"> else if (state == STATE_IN_WORD) { </pre>| <pre lang="C"> } else if (state == STATE_IN_WORD) { </pre> |

Debería haber un espacio previo al ( del *if*
|Incorrecto | Correcto|
|------------ | -------------|
|<pre lang="C"> if(strchr(delim_words, c) != NULL) { </pre> | <pre lang="C"> if (strchr(delim_words, c) != NULL) { </pre>|

Los punto y coma no deberían llevar un espacio antes de su utilización
|Incorrecto | Correcto|
|------------ | -------------|
|<pre lang="C"> return next_state ; </pre> | <pre lang="C"> return next_state; </pre>|

Usar *snprintf* en vez de *strcpy*
|Incorrecto | Correcto|
|------------ | -------------|
|<pre lang="C"> strcpy(); </pre> | <pre lang="C"> snprintf(); </pre>|

El *else* debería haber estado en la misma linea que el } que cierra el bloque previo. Además, si tiene una llave a derecha o izquierda debería estar la correspondiente del lado opuesto.
|Incorrecto | Correcto|
|------------ | -------------|
|<pre lang="C"> else {  </pre>| <pre lang="C"> } else { </pre> |

Las lineas deberian tener como máximo 80 caracteres

2. <br> ![Captura errores generación paso1](/images/errorGeneracionPaso1.png) <br> Al poner el flag -c se genera codigo objeto sin linkear (precompilación + compilación). De esta manera ya sabemos que son errores de compilación y no de linkeo. Lo que ocure es que el compilador no tiene la información suficiente acerca de los tipos y nombres de funciones que aparecen en el código, de ahi que indica *unkown type* y definición implicita. Incluso podrían ser errores de tipeo. Esto podría solucionarse indicándole al compilador que existe ese tipo y esas funciones, declarándolas al principio del archivo por ejemplo. Incluso no haria falta indicar que hacen las funciones, con solo asegurarle al compilador que existen alcanzaria. También hay que tener en cuenta que los errores viene luego de una linea en la que se indica que se generaba codigo objeto a partir de un .c, esta etapa corresponde al compilador, el linker justamente *linkea* los .o
3. El sistema no reportó ningún *Warning* ya que el flag -Werror indica que todos los warnings son tratados como errores.


## Paso 2 - Errores de generación 2

1. En el *main.c* se agregó `#include "paso2_wordscounter.h"` con las declaraciones de tipos y funciones, se reemplazó `strcpy(filepath, argv[1]);` por  ` memcpy(filepath, argv[1], strlen(argv[1]) + 1);` y se colocó el *else* en la misma linea que el } previo. <br> En el *paso2_wordscounter.c* se modificó de tal manera que pase las normas de codificación pero se invirtió el orden de los include, donde ahora primero se incluye el *paso2_wordscounter.h* y luego las librerías necesarias. <br> El *paso2_wordscounter.h* no tuvo modificaciones.

2. <br> ![verificacion de normas de programacion](/images/normasProgramacionPaso2.png)
3. <br> ![Error generación de código](/images/errorGeneracionPaso2.png) <br> El compilador lee los *#include* de arriba hacia abajo, por lo que al poner primero el .h y luego las librerías que precisa, arrojará los errores de tipo desconocido, tanto para *size_t* como para *FILE*. <br> Los errores en *words_counter_getwords* vienen de llamar a la función antes de declararla <br> Finalmente, el compilador no reconoce a la función *malloc* ya que ni se encuentra definida por el programador como una funcion propia, ni se incluyó la librería *stdlib.h* que es quien la contiene.

## Paso 3 - Errores de generación 3
1. En el *paso3_wordscounter.c* se agregó un *include* con *stdlib.h* y en *paso3_wordscounter.c* se agregaron *includes* para *string.h* y *stdio.h*
2. <br> ![Error generación de codigo](/images/errorGeneracionPaso3.png) El mensaje de error se da al momento del *linkear* *paso3_wordscounter.o* y *paso3_main.o*. Esto se da porque la función *wordscounter_destroy* es invocada en *paso3_main.c*, declarada en *paso3_wordscounter.h* pero no implementada en *paso3_wordscounter.c*

## Paso 4
1. Se agregó la implementación de *wordscounter_destroy* en *paso3_wordscounter.c*
2. <br> ![Tda](/images/resultadoTdaValgrindPaso4.png) <br>En la linea 14 de *paso4_main.c* se abre un archivo que luego no se cierra. <br> En la linea 24 se pierde memoria porque *wordscounter_process* internamente llama a *wordscounter_next_state()* que pide memoria con malloc pero no la libera. <br> Al momento de salir de la ejecución hay 5 *FILE DESCRIPTORS* que no se cerraron: el correspondiente a input_tda.txt, uno de *valgrind*, otro correspondiente a *stderr*, otro a *stdout* y otro a *stdin*.
3. <br> ![Long Filename](/images/resultadoLongFileNameValgrindPaso4.png) <br> reporta un buffer overflow en la linea 13 de *paso4_main.c*, esto se da porque se le pasa a *memcpy* un buffer de tamaño insuficiente, entonces no lee la dirección completa. <br> También hace referencia a 4 *FILE DESCRIPTORS* abiertos al momento de finalizar la ejecución del programa: 3 de entrada, salida y error estándar; y uno de *valgrind*.
4. *strncpy* a diferencia de *memcpy*  lee la cantidad indicada o hasta que encuentra un caracter nulo. En este caso no huebiese habido buffer overflow pero no se hubiese leido la dirección en su totalidad.
5. *Segmentation fault* ocurre cuando se intenta acceder a una posición de memoria no permitida, *buffer overflow* ocurre cuando se almacena en un *buffer* más información de la que es posible, escribiendo el excedente en memoria contigua no asignada para tal fin. Dado un *buffer overflow*, puede ocurrir un *segmentation fault*


## Paso 5
1. en *paso5_main.c* se abre el archivo unicamente con *fopen*, sin ningún buffer del programa. En caso de que el input no sea por STDIN, se cierra el archivo abierto. En *paso5_words_counter.c* ya no se pide memoria para los caracteres delimitadores, se resuelve sin la necesidad de *malloc()*
2. <br> ![motivo Sercom fallan pruebas](/images/errorPruebasPaso5.png) <br> Las pruebas fallan dado que el valor esperado fue distinto al obtenido, esto lo indica Sercom mostrando las diferencias entre los esperado y obtenido. En el primero caso se esperaba como resultado 1 y se obtuvo 255, en el segundo se esperaba 1 y se obtuvo 0.
3. <br> ![hexdump single word](/images/hdPaso5.png) <br> El último caracter que muestra el comando hexdump es el 64, que yendo de hexadecimal a ASCII representa la letra d.
4. <br> ![corrida single word gdb](/images/corridaGdbPaso5.png) <br> *info functions* devuelve el nombre de todas las funciones definidas en el programa. <br> *list worscounter_next_state* se posiciona en el principio de esta funcion e imprime desde alli las primeras 10 líneas, *list* imprime desde donde se este posicionado, las siguientes 10 líneas. <br> *break 45* indica que se frene la ejecución del programa en la linea 45. <br> *run input_single_word.txt* corre el programa con el input indicado. <br> *quit* sale de gdb. <br> El debugger no se detuvo en la línea indicada porque no pasó por la misma. De lo contrario el resultado obtenido no hubiese sido 0. Al ingresar a *wordscounter_next_state* luego de terminar la primera palabra sale al ser *c* un EOF (-1 en *int*). Para verificar esto último se usaron los comandos *print*, *next*, *break* y *step*

## Paso 6
1. Se redefinió la constante error y los caracteres delimitadores como una constante. Además, se invirtió el orden en que se hacían las evaluaciones: ahora primero se evalúa el estado y luego se compara el caracter. Se agregó entonces el caso en que si *c == EOF* puede llegar a tener que sumarse una palabra depediendo del estado.
2. <br> ![entregas realizadas](/images/submissionPaso6.png) <br>
3. <br> ![prueba single word local](/images/singleWordPaso6.png) <br>

## Paso 7 

## Paso 8
1. -l por listen, quiere decir que está escuchando a la espera de una conexion. -p sirve para indicar el puerto.
2. <br> ![netcat puerto en espera](/images/netcatScreen.png) <br>
3. El input de una consola es la salida en el primer netcat
4. 3, dos ESTAB y uno LISTEN <br> ![netcat varios](/images/netcatScreen2.png) <br>
5. Tiburoncin indica la cantidad y los bytes enviados de A a B. Además indica si B los recibió (sync) o no (behind). Se relaciona con hexdump en que tiburoncin imprime algo muy similar a lo que se obtendria de hacer un hexdump de un archivo conteniendo lo enviado por A. Es *Man in the middle* porque toma los bytes enviados por A, los examina y deja que sigan hacia destino
6. <br> ![cat AtoB](/images/catAtoB.png) <br>
   <br> ![hex AtoB](/images/hexAtoB.png) <br>
