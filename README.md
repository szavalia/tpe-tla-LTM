# Trabajo práctico especial LTM

## Datos de la materia
72.39 Autómatas, Teoría de Lenguajes y Compiladores
Comisión S

## Información del grupo
### Nombre 
 Los Tres Mosqueteros

### Integrantes
*   Ana Cruz, legajo 60476
*   Salustiano Zavalía Pángaro, legajo 60312
*   Valentino Riera Torraca, legajo 60212


---
## Antes de empezar...
*   Requisitos:
    *   tener instalado gcc, bison y flex
    * tener clonado el repositorio de git del grupo. 

## Como correr nuestro compilador
Dentro de la carpeta compiler hay un archivo  `makefile`. Este se encarga de "instalar" el proyecto y de compilarlo, para facilitar el uso. 
Para tener todo listo para empezar, habria que hacer: 

    $ make install
    $ make
    
Lo cual generará un archivo compiler.out. 

::: warning
//COMPLETAR ESTA PARTE POR QUE NO SE COMO VA A SER LA VERSION FINAL
:::

---
# Sobre el lenguaje

## Introducción
No fue tarea sencilla pensar el lenguaje que ibamos a querer generar para este trabajo practico. Teniamos en claro que queríamos algo útil, con algún uso de caso real que nos pareciera relevante. Tambien queriamos algo que no fuera excesivamente rebuscado, ya que el objetivo no era hacer un lenguaje increiblemente innovador, si no que queríamos aplicar los temas vistos en la materia. Estabamos pensando que queríamos hacer una minimizacion de C, que requiera menos clicks para generar el mismo codigo. 

Fue así como llegamos a la idea de "uno a la vez", un lenguaje que se plantea como objetivo solo usar caracteres que no necesiten de un segundo click para ser activadas (como sería poner un parentesis, que tendríamos que apretar shift + 8). Nos pareció que este lenguaje podría serle de utilidad a gente con alguna discapacidad que solamente le permita tener una mano en el teclado, o todavia mas restrictivo, que use un mouth stick para escribir, lo que dificultaría mucho usar C tradicional.

Para esto, nos basamos en el teclado [United States](https://upload.wikimedia.org/wikipedia/commons/5/51/KB_United_States-NoAltGr.svg) como figura en el link. 

---

# La gramática
El lenguaje "uno a la vez" tiene muchas semejanzas con C. En esta sección iremos listando como se usan las funciones disponibles. 

Es importante notar que para disminuir la cantidad de teclas que hay que presionar se omitió el uso de `;` y en cambio se separan las operaciones con enters.
Tambien usamos llaves cuadradas en lugar de paréntesis para marcar parametros o indicar precedencia en las operaciones aritméticas.

## Variables
*   Para declarar una variable numérica se usa el identificador `num`. Este siempre representa un double. Una definición modelo de una variable sería así:

        num varNumerica = 4

    El lenguaje también permite declarar variables sin inicializarlas, en cuyo caso agregaría el enter despues del nombre.



*   Para declarar una variable de tipo string, o su equivalente en c, vector de chars, uso el identificador `s`. Por ejemplo:

        s varTextual = 'Un string de prueba'
    Como para usar comillas dobles deberíamos apretar la tecla `shift`, se optó por usar las comillas simples y no permitir la definicion de variables tipo chars, que serían las que en C deberían ir entre comillas simples. 


*   Para declarar una variable booleana usamos el identificador `b`. Los valores `TRUE` y `FALSE` siguen la misma regla que venimos aplicando hasta ahora y se invocan mediante su inicial. Un ejemplo en el que se define una variable como true:

        b booleanoTrue = t


## Imprimir
Para esta sección generamos dos funciones: `ps` y `pi`. Estas son una réplica de lo que en C seria un printf con `%s` o `%d` respectivamente. La idea de esto es que si se quiere imprimir el valor de una variable de tipo string o un string literal se invoque a la función ps, mientras que si quisieramos imprimir una variable numérica llamariamos a pi. 
Por ejemplo, estas dos ejecuciones obtienen el mismo resultado:

    s varString = 'hola'
    ps varString
    ps 'hola'

Por otro lado, un ejemplo de uso para pi sería:

    num varNum = 45
    pi varNum


## Secciones condicionales
Por el momento la gramática acepta dos condicionales, el `if` y `do while`. 

*   Para usar el if lo invoco de la siguiente manera:

        if [ expresión condicional ]
            ... contenido ...
        fi
    Es muy importante el uso de los enters como se muestra en el ejemplo, ya que al no poder usar llaves usamos los enters como separadores, y fi para delimitar el fin del condicional. 

*   Para usar el do while tenemos una modalidad similar que para el if:

        do
            ... contenido ...
        w [ expresión condicional ]

Para ambos casos, contenido puede ser cualquiera de las funcionalidades que el lenguaje ofrece. Mencionaremos mas sobre la expresión condicional en la siguiente sección.

## Expresiones condicionales
Para armar las expresiones condicionales usamos dos variables (pueden ser variables definidas o valores definidos in situ) unidos por los operadores que conocíamos de bash. Estos representan ==, !=, <, <=, >, >= :

     EQ | NE | LT | LE | GT | GE
Estas expresiones pueden concatenarse entre si usando las expresiones `and` u `or`. 






# Referencias

_Brown, D., Levine, J., & Mason, T. (1995). Lex & Yacc (Second ed.). O’Reilly Media. https://www.campus.itba.edu.ar_



