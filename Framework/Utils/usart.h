/*! {{{
  \file usart.h

  \brief

  }}} */

#ifndef USART_H
#define USART_H

#ifdef __cplusplus
 extern "C" {
#endif

int usart_putchar( int ch );

int usart_getchar();

void init_usart( int speed );

#ifdef __cplusplus
 }
#endif

#endif /* ifndef USART_H */

/* {{{ Modeline for ViM
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

