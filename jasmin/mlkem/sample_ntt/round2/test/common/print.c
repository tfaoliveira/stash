#include <inttypes.h>
#include <stdio.h>

void print_u16(const uint16_t *ptr, size_t length)
{
  size_t i;

  if(length == 0) { return; }

  printf("{\n  ");
  for(i=0; i<(length-1); i++)
  { printf("0x%04" PRIx16 ", ", ptr[i]);

    if((i+1)%8 == 0)
    { printf("\n  "); }

    if((i+1)%256 == 0)
    { printf("\n  "); }
  }

  printf("0x%04" PRIx16 "\n};\n", ptr[i]);
  return;
}

void print_u8(const uint8_t *ptr, size_t length)
{
  size_t i;

  if(length == 0) { return; }

  printf("{\n  ");
  for(i=0; i<(length-1); i++)
  { printf("0x%02" PRIx8 ", ", ptr[i]);

    if((i+1)%8 == 0)
    { printf("\n  "); }

    if((i+1)%256 == 0)
    { printf("\n  "); }
  }

  printf("0x%02" PRIx8 "\n};\n", ptr[i]);
  return;
}

// u8 _c_ompressed version
void print_u8c(const uint8_t *ptr, size_t length)
{
  size_t i;

  if(length == 0) { return; }

  printf("0x");
  for(i=0; i<(length-1); i++)
  { printf("%02" PRIx8 "", ptr[i]); }
  printf("%02" PRIx8 "\n", ptr[i]);

  return;
}


