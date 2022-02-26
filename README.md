# Taller de Programacion 1 - Veiga

## Proceso de compilación

C es un lenguaje portable. Puedo llevar el mismo programa de una plataforma a otra, tengo que tener compilador C en la otra plataforma que respete el estandar. Ademas prestar atencion a los tamaños de objetos (usar sizeof, etc). Esto me aseguraria que funcione.

</br>

Para ser estandar un compilador debe tener:
* respetar sintaxis 
* Proveer conjunto de librerias estandar (stdlib, stdio, etc)
*  Respetar un proceso de compilación (transformacion desde codigo fuente hasta ejecutable final)

![image](https://user-images.githubusercontent.com/71232328/155787261-4a435fd9-d670-4711-8a14-b03bb329b652.png)

</br>

Transformacion de uno o más codigos fuentes. Esto porque los proyectos grandes se hacen de forma modular. Ahi entra el concepto de declaracion, definicion, scope, etc

![image](https://user-images.githubusercontent.com/71232328/155788272-10e8716e-3757-49b2-aa6a-4a44c7f04a71.png)

</br>

En precompilacion se toma el archivo tal cual fue escrito y se resuelve las instrucciones de precompilacion (empiezan con #, por ejemplo los include, comentado de líneas, definicion de variables, etc). Como salida son archivos de C puro. Estos se tranforman en archivos objeto en la etapa de compilacion. Verifica sintaxis, llamadas a funciones correctas, asignaciones, etc. El resultado son modulos objetos (casi ejecutable). Puede haber llamado a funciones dentro de los mismos o por fuera. la etapa de link edicion combina los llamados cruzados hasta generar el código ejecutable.

En la primera etapa puede haber errores de includes que no existen, malas definiciones en las macros
En compilacion los errores son de sintaxis o en los llamados a funciones (mal declaradas)
En link edicion aparecen ambiguedades (funciones con mismo nombre ya declaradas, que noe existen, etc)

Cuando se pone #define se va armando una tabla con los símbolos correspondientes, el precompilador hace find and replace

![image](https://user-images.githubusercontent.com/71232328/155790994-734ce591-f327-49a5-9ea3-ffcda0d03fd2.png)


Las instrucciones a continuacion agregan lógica en la etapa de precompilación. Se llaman instrucciones de precompilacion


![image](https://user-images.githubusercontent.com/71232328/155791200-484509d3-33a7-4d47-856c-39c1776b21d3.png)

En este caso le paso al compilador un printf, y una línea en blanco

Hay 2 tipos de include: con <> y con "". Hoy no hay diferencia. Si alguien hace dos veces el include del archivo, la primera vez lo defino al simbolo y compilo el resto, la segunda vez que lo incluya (por error) ya estará definido el símbolo, aqui nos salva el ifndef __ARCHIVO_H__. Si no se hace esto, habrá un *warning*

![image](https://user-images.githubusercontent.com/71232328/155792093-b240b322-36ff-4ca8-bb7e-8f72dc79d730.png)

La definicion de macros siempre hace find an replace. Pero es distinto a un llamado a función. OJO. Se expande directamente. En el caso de sqr(3+2) el comportamiento no va a ser el esperado. Hay que agregar paréntesis en las macros

![image](https://user-images.githubusercontent.com/71232328/155792709-93c37555-87ca-4aab-8f14-044e97d301d2.png)

En la compilacion hay tres fases. Recibimos programa C. El parseo reemplaza los símbolos, verifica sintaxis. Luego traduccion a assembler y finalmente Ensamblador instruccion a instruccion a codigo máquina. solo falta resolver llamados a funciones externas

![image](https://user-images.githubusercontent.com/71232328/155793859-36574910-c43a-4d96-a9f6-3a18a178e4d5.png)


En Link Edicion, se resuelven las llamadas a funciones definidas por fuera de los modulos donde son llamadas.

![image](https://user-images.githubusercontent.com/71232328/155794264-2e33106f-514d-48ab-af69-67f4a388ab25.png)

## Memoria en C/C++

El tamaño que ocupa cada variable depende de la arquitectura y del compilador. Las variables se alinean con direcciones de meoria que son multiplos de 2, 4, etc. Por cuestiones de electronica es más facil para acceder. Por eso las ordena de esta manera el compilador. Desperdicia espacio (padding) Los punteros son las direcciones de memoria donde empieza algo (char, int, str, etc). Los punteros son variables enteras del mismo tamaño.
Las cadenas de caracteres terminan con un bara cero o caracter nulo (byte 0). Las cadenas se guardan en memoria con el caracter ascii.

![image](https://user-images.githubusercontent.com/71232328/155800920-fe91e108-a356-4768-8c64-71f43390e383.png)


Estructuras de datos. Agrupan variables. De esta forma va a ocupar 16 bytes, pero todos estarán alineados

![image](https://user-images.githubusercontent.com/71232328/155802169-91a3221a-221d-4d32-a6f1-dd9d8b02b0c7.png)


Con el atributo especial de gcc __attribute__((packed)) el compilador empaqueta los campos sin padding, más eficiente en memoria pero más lento. Por ejemplo para leer s.c hay que hacer 2 lecturas

![image](https://user-images.githubusercontent.com/71232328/155802295-94a5649b-557a-4c1a-8c97-c3324a965a7a.png)

El endianess indica en que orden almacenaremos los bytes. Big endian: el mas significativo primero. El byte más significativo se lee/escribe primero (o esta primero en la memoria) en las arquitecturas big endian. Little endian pone en orden contrario, del menos significativo al más significativo.

Esto no tiene importancia salvo cuando se interpreta ints como tira de charts (por ejemplo en las comunicaciones a través de sockets). Por esto es que siempre hay que especificar el endianess en que se guardan/envian archivos

![image](https://user-images.githubusercontent.com/71232328/155802519-33df7dc5-0d10-4a39-ab9f-b2975d365054.png)

Puede modificarse el endianess (el de la red es big endian). Para usar las funciones hay que hacer: #include <arpa/inet.h>.


![image](https://user-images.githubusercontent.com/71232328/155802856-5dc7e7c7-beea-4fb5-a857-84d628e2eab6.png)


#### Segmentos de memoria.

En el code segment no se pueden modificar, se mantiene constante. 
En el stack van las variables de retorno y direcciones de funciones.
Si hacemos malloc, la memoria se reserva en el heap.

![image](https://user-images.githubusercontent.com/71232328/155803038-74430106-626e-4171-87b7-add051ce3c7e.png)

Variable Global, se pone en el data segment y el lifetime es de todo el programa.

Si pongo varaible static, va al data segment y el lifetime es desde que se carga el programa hasta que termina.

Si hablamos de una variable local en una funcion, se aloca en el stack. Se le asigna al momento de llamada de la funcion y cuando cierro llave, se libera. El lifetime es desde inicio hasta finalizacion de funcion.

Scope habla de la accesibilidad. 

![image](https://user-images.githubusercontent.com/71232328/155803459-d50870be-014a-4513-a695-e9eb92ccbb4f.png)


Ejemplo. Static indica que solo se puede usar desde el mismo archivo (no desde afuera). Sin static es global. Static dentro de funcion indica que se debe conservar su valor entre llamados.

char * c = "ABC". La cadena estará en el code segment por ser una constante, no la podré modificar
ar[] es un arreglo de caracteres, por lo que estan en el stack. Por lo tanto lo puedo modificar. Si quiero hacer esto con char * c dará error.


![image](https://user-images.githubusercontent.com/71232328/155803914-1ca50704-eaec-4d43-8540-836533051733.png)

Como el puntero "a" apunta al Code Segment y este es de solo lectura, tratar de modificarlo termina en un Segmentation Fault

![image](https://user-images.githubusercontent.com/71232328/155805022-b128413a-2f03-4198-9fc5-2eb5885df1d4.png)


#### Punteros



![image](https://user-images.githubusercontent.com/71232328/155805139-1a39cd78-7ea0-4685-b819-d28032e37ad0.png)


Aritmetica de punteros. La notación de array (indexado) y la aritmética de punteros son escencialmente lo mismo. La aritmética de punteros se basa en el tamaño de los objetos a los que se apunta al igual que el indexado de un array.
Al hacer p + 1 se incrementa en 1 * sizeof(int) entonces va al siguiente elemento del arreglo.



![image](https://user-images.githubusercontent.com/71232328/155805426-6ffb7628-4d7d-493a-ae88-f07c9a53225f.png)


Punteros a funciones. Para especificar el criterio de comparacion en quick sort la puedo pasar con el puntero a funcion.

![image](https://user-images.githubusercontent.com/71232328/155805752-62c4c52d-4494-450a-b48c-4061570565d8.png)

Como leer la notacion. Otra forma en el link: http://c-faq.com/decl/spiral.anderson.html

![image](https://user-images.githubusercontent.com/71232328/155806479-2aff503b-4393-4eb8-bb35-b6e283efdfca.png)
![image](https://user-images.githubusercontent.com/71232328/155806491-6c70e4a3-2b49-4362-8fdf-50f37b5bbf52.png)
![image](https://user-images.githubusercontent.com/71232328/155806511-a7bad8e7-a7c9-4f73-aba6-66323f56aac6.png)

Con el typedef le estoy indicando al compilador

![image](https://user-images.githubusercontent.com/71232328/155806527-bb1799f4-7b73-424a-86ac-e7bb40c65340.png)

#### Buffer overflows

el primer argumento es el nombre del ejecutable, argc es la cantidad de argumentos, y argv es un arreglo de n punteros a char (argumentos pasados por linea de comandos).

Define variable cookie, queda en el stack.
Define arreglo de 10 char, tambien en el stack (ya lleva 14 bytes)
%08x es en hexadecimal, simbolos hexadecimales en minuscula, en 8 caracteres padeados con cero. Si pongo algo mas grande que diez bytes, me va a pisar la memoria de cookie.

![image](https://user-images.githubusercontent.com/71232328/155810097-c2f5c612-7b0a-4cd5-9776-34ad38818d8a.png)

* Es claro que al inicializar cookie a cero nunca se va a imprimir "You win!"... o si?.
* gets lee de la entrada estándar hasta encontrar un ’\n’ y lo que leea lo escribira en el buffer buf. Pero si el input es más grande que el buffer, gets escribira por fuera de este y sobreescribira todo el stack lo que se conoce como Buffer Overflow.
* Para hacer que el programa entre al if e imprima "You win!" se debe forzar a un buffer overflow con un input crafteado:
* Debe tener 10 bytes de mínima para ocupar el buffer buf.

* Posiblemente deba tener algunos bytes adicionales para ocupar el posible espacio de padding usado para alinear las variables.
* Luego se debe escribir los 4 bytes que sobreescribiran cookie pero cuidado, dependiendo de la arquitectura y flags del compilador sizeof(int) puede no ser 4.
* Suponiendo que sean 4 bytes, hay que escribir el número 0x41424344 byte a byte y el orden dependera del endianess: "ABCD" en big endian, "DCBA" en little endian.

![image](https://user-images.githubusercontent.com/71232328/155810692-00ab9f59-c7b8-4715-aed5-596afb41ebcb.png)

getline es más segura, permite pasar un tamaño. Mas seguro que gets. en vez de strcpy, usar strncpy que permite pasar tamaño máximo

El primer argumento del printf va al stack, entonces se puede pisar y que imprima you win, etc.

![image](https://user-images.githubusercontent.com/71232328/155810879-9ea81763-8009-43b5-8a1c-0ce5768ca530.png)

## Sockets TCP/IP en C

Dado que el medio es compartido, cuando Alice envia un mensaje este se propaga por toda la red. El mensaje es recibido entonces por todos los participantes. Y a la vez evita que otros puedan comunicarse por que el medio esta en uso. Esto se conoce como half duplex.  Este tipo de redes requieren un hardware adicional mínimo o nulo lo que las hace particularmente baratas y fáciles de mantener. Son para redes locales, como una red Wifi.

![image](https://user-images.githubusercontent.com/71232328/155849448-fcc31e22-2647-4d51-b5e1-2b29af631b92.png)

Ahora la red esta segmentada: los mensajes son enviados de un segmento a otro a traves de los routers.
Los routers usan las direcciones IP de destino para saber a donde enviar los mensajes. La red esta governada por el protocolo IP. Existen actualmente 2 versiones IPv4 e IPv6. El primero usa direcciones de máquina (host) de 4 bytes y el segundo de 16. IP no garantiza que lleguen todos los paquetes, ni el orden ni que no haya duplicados. Es un protocolo pensado para simplificar el hardware de la red, no para hacerle más fácil la vida a los desarrolladores.

El orden de los mensajes no se garantiza en esta red. Otro error podria ser que los mensajes o paquetes lleguen duplicados. Pueden perderse tambien. IPv4 usa direcciones de 4 bytes. IPv6 usa direcciones de 6 bytes.

![image](https://user-images.githubusercontent.com/71232328/155849482-c0c263e6-4371-4bff-8e7c-bb08f45096b2.png)

IP solo nos habla de los hosts, no de los programas que corren en ellos. TCP permite direccionar a cada programa o servicio a traves de un número, el puerto. TCP es orientado a la conexión: hay un participante pasivo que espera una comunicación y hay otro que la inicia de forma activa. Típicamente el participante pasivo es el servidor y el activo el cliente. Una vez establecida la conexión los bytes enviados (full duplex) no se pierden, desordenan ni duplican. TCP no garantiza nada sobre los mensajes, solo sabe de bytes, por lo que un mensaje puede llegar incompleto.


El protocolo TCP está sobre la red IP. Se envian bytes. El protocolo TCP garantiza el orden y que los bytes no se pierdan (los reenvia si se pierden en la red). TCP no tiene mensajes, envía tira bytes.

Short read, es leer de menos. Cada máquina, ademas de tener una direccion tiene varios puertos que son programas escuchando. Podemos hablar con la misma máquina pero para servicios distintos porque hay varios programas escuchando en distintos puertos.

![image](https://user-images.githubusercontent.com/71232328/155849687-2414e853-eb4c-42a9-ac4e-87c340a36618.png)

Resuelve los nombres de dominio. Para enviar un mensaje por ej a Bob.com, le envia al servidor dnd "Bob.com" y el servidor le devuelve la direccion ip. El dns nos permite preguntarle a un servidor el ip de una direccion/nombre. Un dominio puede tener varias ips.


![image](https://user-images.githubusercontent.com/71232328/155850334-40c75a3c-9806-487d-a0f1-533307d8cb87.png)


## Resolucion de nombres (TODO ESTO ESTA BIEN CLARO EN EL HANDOUT DEL DIPA SOCKETS)

El servidor tiene que definir desde donde quiere recibir las conexiones. Hay más esquemas posibles pero solo nos interesa definir la IP y el puerto del servidor. Sin embargo, hardcodear la IP y/o el puerto es una mala práctica. Mejor es usar nombres simbólicos: host name y service name. La función getaddrinfo se encargara de resolver esos nombres y llevarlos a IPs y puertos.

![image](https://user-images.githubusercontent.com/71232328/155850536-ec802010-2bfc-4ba0-b779-4914bc67a32e.png)




