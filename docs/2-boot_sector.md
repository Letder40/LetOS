# Boot Sector (Sector de arranque)

## ¿Que es un sector de arranque?
Un sector de arranque no es mas que un binario que en nunca mas de 512 bytes contiene las instrucciones de arranque de un sistema operativo.
Un sector de arranque siempre es identificado por su magic number (0xaa55), un magic es un word (2 bytes) que se usan como un identifificador, de esta manera la BIOS es capaz de identificar un sector de arranque. 
La BIOS suele cargar el sector de arranque en la dirección de memoria 0x7c00, esta información es util para calcular el offset real de los datos definidos en labels en nuestro boot sector.

## 16-bit Real mode (intel)
Para que los software como los sistemas operativos mas antiguos puedan correr en los procesadores modernos, Intel tuvo que implementar la capacidad de emular el procesador mas antiguo de su familia (intel 8086) el cual solo usaba 16 bits.
