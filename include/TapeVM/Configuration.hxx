/* TapeVM/Configuration.hxx
 * Copyright (c) 2025, Christopher Stephen Rafuse
 * BSD-2-Clause
 */
#pragma once

#define TAPE_VERSION_MAJOR 1
#define TAPE_VERSION_MINOR 0
#define TAPE_VERSION_PATCH 0

#if defined(TAPE_STANDALONE)
  #if defined(_WIN32)
    #define __TapeVM_Windows__
  
  #elif defined(__unix__)
    #define __TapeVM_UNIX__
  
    #if defined(__linux__)
      #define __TapeVM_Linux__
      
    #elif defined(__FreeBSD__) || defined(__FreeBSD_Kernel__)
      #define __TapeVM_FreeBSD__
  
    #else 
      #error TapeVM does not support this UNIX system
    #endif
  
  #else 
    #error TapeVM does not support this operating system
  #endif
  
  
  
  #if defined(__TapeVM_Windows__)
    #define __TapeVM_Export__ __declspec(dllexport)
    #define __TapeVM_Import__ __declspec(dllimport)
  
  #else
    #define __TapeVM_Export__ __attribute__((__visibility__("default")))
    #define __TapeVM_Import__ __attribute__((__visibility__("default")))
  #endif
  
  
  #if defined(TAPE_EXPORTS)
    #define TapeAPI __TapeVM_Export__ 
  #else 
    #define TapeAPI __TapeVM_Import__ 
  #endif
  
#else 
#include <NoctSys/Configuration.hxx>
  #if defined(TAPE_EXPORTS)
    #define TapeAPI __NoctSys_Export__ 
  #else 
    #define TapeAPI __NoctSys_Import__ 
  #endif
#endif
