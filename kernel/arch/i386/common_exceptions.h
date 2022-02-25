#pragma once

#include "idt.h"

void install_exception_handlers();

INTERRUPT void divide_by_zero_interrupt(struct interrupt_frame* frame);
INTERRUPT void debug_interrupt(struct interrupt_frame* frame);
