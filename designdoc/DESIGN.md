# Design Document for the Exokernel

It is my hope that this design document can provide a sort of overview and a technical layout of the goals of this project. Hopefully, with this design document, I can lay out the vision of the project and necessary components of that vision.

## Overview

## Context

## Goals and non goals

## Milestones

## Existing Solution
Talk about how users interact with this system and/or how data flows through it

## Proposed Solution

## Alternative Solutions

## Testability/Monitoring/Alerting

## Cross team impact

## Open Questions

## Detailed Scoping and Timeline

## 1. Problems

- How to we define the libOS interface?
    - What should the format of a libOS be? A dynamically linked library? Or something else? Like a server/daemon?
- How should we expose resource allocation, physical names and revocation?
- How should we implement secure bindings?
    - Hardware mechanics
    - Software caching
    - Downloading code into the kernel
    - Software TLB for commonly used addresses?
- What rules should be used to download code into the kernel?
- What does the boot process look like?
- How do we do all this while trying to avoid resource management and stick to security?
- How do we expose "book keeping structures" to libOS's?
- How do we solve network demultiplexing?

## 2. Solutions

### 2.1 The Boot Process
When the computer boots up, GRUB (or another adequate multiboot2 loader) will load our custom loader.elf, which sets up long mode and then loads the actual exokernel to take over the computer.

#### 2.1.1 x64 Specific State

I've chosen to use the LP64 model of x64 for this project, so longs and pointers are 64-bit and integers are 32 bits.

### 2.2 The LibOS Interface