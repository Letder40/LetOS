# VGA
---

VGA (video graphics array) Lo unico que es necesario de comprender de VGA para el desarrollo de un sistema operativo básico es que es un componente de hardware que se comunica con el monitor para determinar como este se va a comportar.
Este para x86 protected mode esta mapeado en los siguientes rangos:

+ ```0xA0000```: EGA/VGA graphics modes (64 KB)
+ ```0xB0000```: Monochrome text mode (32 KB)
+ ```0xB8000```: Color text mode and CGA-compatible graphics modes (32 KB)

```c
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

// Color text mode
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
```

## Funciones definidas para manipular VGA

```c
static inline color vga_entry_color(VGA_COLOR foreground, VGA_COLOR background);
static inline uint16_t vga_entry(uint8_t uc, color color);

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
```


## Incializando el buffer
En en el rango de direcciones de memoria en el que estoy trabajando se espera que cada entrada del array sea un uint16_t, en otras palabras 16 bits por cada entrada:

**Entrada buffer VGA**:
+ **8bits**: char ascii.
+ **8bits**: color.
    + **4bits**: foreground.
    + **4bits**: background.


```c
void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH  + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}
```
