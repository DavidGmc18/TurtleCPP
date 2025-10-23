#pragma once

#ifdef _WIN32
  #ifdef TURTLE_EXPORTS
    #define TURTLE_API __declspec(dllexport)
  #else
    #define TURTLE_API __declspec(dllimport)
  #endif
#else
  #define TURTLE_API
#endif