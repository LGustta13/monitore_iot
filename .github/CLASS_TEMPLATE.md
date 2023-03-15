 - Arquivo .cpp
```c++
/*
  <Object>Services.cpp - Biblioteca para <descrição>.
  Criado pelo <usuário>, <data>.
*/

#include "<Object>Services.h"

<Object>Services::<Object>Services()
{

    setup<Object>();
}

void <Object>Services::setup<Object>(void)
{
}

void <Object>Services::<funcionalidade>(void)
{
}
```

- Arquivo .cpp
```c++
/*
  <Object>Services.h - Biblioteca para <descrição>.
  Criado pelo <usuário>, <data>.
*/

#ifndef <Object>SERVICES_H
#define <Object>SERVICES_H

#include <Arduino.h>

class <Object>Services
{
public:
  /** Descrição
   * @param -
   * @return -
   */
  <Object>Services(void);

  /** Funcao que realiza o setup dos pinos
   * @param - void
   * @return - void
   */
  void setup<Object>(void);

  /** Descrição
   * @param -
   * @return -
   */
  void <funcionalidade>(void);
};

#endif
```

- Arquivo .ino
```c++
/*
  Services.ino - exemplo de uso das funções
  Criado pelo <usuário>, <data>.
*/

/*
  Orientações:
*/

/*
  Parâmetros de <Object>Services:
  * se necessário!
*/

#include "<Object>Services.h"

<Object>Services <Object>();

void setup() 
{
  
}

void loop()
{
  
}
```

- keywords.txt
```
#######################################
# Syntax Coloring Map
#######################################

#######################################
# Datatypes (KEYWORD1)
#######################################

<Object>Services KEYWORD1

#######################################
# Methods and Functions (KEYWORD2)
#######################################

setup<Object>  KEYWORD2
<funcionalidade>   KEYWORD2
```
