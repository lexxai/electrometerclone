/* 
 * File:   unionLATC.h
 * Author: lex
 *
 * Created on 7 червня 2014, 20:55
 */

#ifndef UNIONLATC_H
#define	UNIONLATC_H

#ifdef	__cplusplus
extern "C" {
#endif

volatile union {
    unsigned char byte;
    PORTCbits_t bits;
} LATPORTC;

#define LATPORTC_FLUSH PORTC = LATPORTC.byte

#ifdef	__cplusplus
}
#endif

#endif	/* UNIONLATC_H */

