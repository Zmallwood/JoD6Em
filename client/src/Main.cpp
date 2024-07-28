// Copyright (c) 2024 Andreas Åkerberg.

#include "Core.h"

int main(int argc, char *argv[])
{
  /* Catch all exceptions that can happen during execution. */

  try
  {
    /* Run new instance of the game. */

    jod::RunNewClientInstance();
  }
  catch (const std::exception &e)
  {
    std::cout << "Error: " << e.what() << std::endl;

    /* An exception occured, exit game. */

    return EXIT_FAILURE;
  }

  /* No exceptions occured. */
  
  return EXIT_SUCCESS;
}