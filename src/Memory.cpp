#include "../include/Memory.h"
#include <cstdio>

Memory::Memory()
{
  memoryArray.fill(0);
}

void Memory::dumpMemory(uint16_t start, uint16_t stop)
{
  int count = 0;
  std::for_each(memoryArray.begin() + start, memoryArray.begin() + stop,
                [&count, start](uint8_t i) {
                  printf("0x%04x: 0x%02x\n", start + count++, i);
                });
}

void Memory::injectBoot()
{
  //logo is injected into cardrige only for testing purposes
  std::copy(logo.begin(), logo.end(), memoryArray.begin() + logoAdr);
  std::copy(bootstrap.begin(), bootstrap.end(), memoryArray.begin());
}

void Memory::P1Call(uint16_t, uint8_t)
{
}

void Memory::clean()
{
  memoryArray.fill(0);
}

uint8_t Memory::readByte(uint16_t address) const
{
  return memoryArray[address];
}

void Memory::writeByte(uint16_t address, uint8_t byte)
{
  memoryArray[address] = byte;

  auto it = std::find(IOregs.begin(), IOregs.end(), address);
  if (it != IOregs.end())
    (this->*it->Memory::IOreg::callback)(address, byte);
}
