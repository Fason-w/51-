#ifndef __NIXIE_H__
#define	__NIXIE_H__

extern unsigned char NixieTable[];

void Nixie_Scan(unsigned char Location, Number);
void Nixie_SetBuf(unsigned char Location, Number);
void Nixie_Loop(void);

#endif