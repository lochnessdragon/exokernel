# Design Document for the Exokernel

It is my hope that this design document can provide a sort of overview and a technical layout of the goals of this project. Hopefully, with this design document, I can lay out the vision of the project and necessary components of that vision.

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

## 2. The Boot Process
When the computer boots up, GRUB (or another adequate multiboot2 loader) will load our custom loader.elf, which sets up long mode, paging and paging structures, and then loads the actual exokernel to take over the computer. It will also load in a custom startup application and transfer to it in x64 user mode. This will mean that most of the resources used by the loader can then be deallocated and used for the kernel/applications.

#### 2.1.1 x64 Specific State

I've chosen to use the LP64 model of x64 for this project, so longs and pointers are 64-bit and integers are 32 bits.

## 3. Kernel Security and (mini-)abstractions

The kernel will avoid giving major abstractions over the hardware. Instead, it will simply confirm that the lib os is only accessing "allowed" resources.

The kernel will expose these syscalls to the library operating system (We have represented them here with c syntax)

```int bind_resource(int name);```
```int revoke_resource(int handle);```

When a resource has been requested by a specific application, it will be bound to that application and will not be able to be used by other applications/processes.

We also want a visible revocation of certain resources. (like cpu time) This would involve a signal to the process that it needs to clean up its structures and get ready for a resource to be revoked, potentially following the UNIX signal pattern.

```int revocation_request(int handle);```
``` int bind_signal(REVOC_REQ, revocation_request);```

## 4. The LibOS Interface
Library OS's will be dynamically linked to the application at runtime in most cases. This will allow them to be shared between applications on the computer. Of course, when I reference a library os, I mean the piece of code that provides abstractions for other code. Therefore, applications could be compiled without the need for an exokernel and therefore could be targeted to this specific os. Due to the dynamic nature of operating system abstractions these days, I will not be defining a base series of abstractions that each lib os has to have. However, I will define a few functions that need to be exported for a library os to work.  

## 5. The UNIX LibOS
The hope behind this project would also be to create a unix library operating system. The goal is that unix applications would be able to be dragged and dropped onto the operating system and they should be able to run over the unix lib os's abstraction. This would require a c runtime environment, but that should also be able to run over the unix lib os as well.
