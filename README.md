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




