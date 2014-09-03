
/****************************************************************************
* Copyright (C) 2012 by Emanuel Foster & Lucien Zuercher *
* *
* Dieses Dokument ist Teil von "comprotocol" *
* *
* Comprotocol ist eine frei zu nutzende Bibliothek. Die Bibliothek wird *
* unter der MIT Lizens veröffentlicht. Jegliche Nutzung auf eigene Gefahr. *
****************************************************************************/
/**
* @file co_document.h
* @author Emanuel Foster, Lucien Zuercher
* @date 1. Jan. 2014
* @brief File containing example of doxygen usage for quick reference.
*
* Here typically goes a more extensive explanation of what the header
* defines. Doxygens tags are words preceeded by either a backslash @\
* or by an at symbol @@.
* @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
* @see http://www.stack.nl/~dimitri/doxygen/commands.html
*/
#ifndef _CO_DOCUMENT_H
# define _CO_DOCUMENT_H

/****************************************************************************
* Includes
****************************************************************************/

# include <systemheader1.h>
# include <systemheader2.h>
# include <box/header1.h>
# include <box/header2.h>
# include "local_header1.h"
# include "local_header2.h"

/****************************************************************************
* Makros
****************************************************************************/

/* Area description */

/**
* setzt das bit auf 0
* @param var Byte bei dem der Wert gesetzt wird
* @param bit Die nummer des bits (0-7)
*/
#define CLEAR_BIT(var, bit) ((var) &= ~(1 << bit))

/****************************************************************************
* Enumirationen & Strukturen
****************************************************************************/

/**
* @brief Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explanation.
*/
typedef enum co_BoxEnum_enum {
  BOXENUM_FIRST, /**< Some documentation for first. */
  BOXENUM_SECOND, /**< Some documentation for second. */
  BOXENUM_ETC /**< Etc. */
} BoxEnum;

/**
* @brief Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explanation.
*/
typedef struct co_BoxStruct_struct {
  int a; /**< Some documentation for the member BoxStruct#a. */
  int b; /**< Some documentation for the member BoxStruct#b. */
  double c; /**< Etc. */
} BoxStruct;

/****************************************************************************
* Funktionen
****************************************************************************/

/**
* @brief Example showing how to document a function with Doxygen.
*
* Description of what the function does. This part may refer to the parameters
* of the function, like @p param1 or @p param2. A word of code can also be
* inserted like @c this which is equivalent to <tt>this</tt> and can be useful
* to say that the function returns a @c void or an @c int. If you want to have
* more than one word in typewriter font, then just use @<tt@>.
* We can also include text verbatim,
* @verbatim like this@endverbatim
* Sometimes it is also convenient to include an example of usage:
* @code
* BoxStruct *out = Box_The_Function_Name(param1, param2);
* printf("something...\n");
* @endcode
* Or,
* @code{.py}
* pyval = python_func(arg1, arg2)
* print pyval
* @endcode
* when the language is not the one used in the current source file (but
* <b>be careful</b> as this may be supported only by recent versions
* of Doxygen). By the way, <b>this is how you write bold text</b> or,
* if it is just one word, then you can just do @b this.
* @param param1 Description of the first parameter of the function.
* @param param2 The second one, which follows @p param1.
* @return Describe what the function returns.
* @see Box_The_Second_Function
* @see Box_The_Last_One
* @see http://website/
* @note Something to note.
* @warning Warning.
*/
BOXEXPORT BoxStruct* f_co_theFunctionName(
  BoxParamType1 pParam1, 
  BoxParamType2 pParam2 /*, 
  ...*/
);

/**
* @brief A simple stub function to show how links do work.
*
* Links are generated automatically for webpages (like http://www.google.co.uk)
* and for structures, like BoxStruct_struct. For typedef-ed types use
* #BoxStruct.
* For functions, automatic links are generated when the parenthesis () follow
* the name of the function, like Box_The_Function_Name().
* Alternatively, you can use #Box_The_Function_Name.
* @return @c NULL is always returned.
*/
BOXEXPORT void* f_co_theSecondFunction(void);

/* Area description */

/**
* Brief can be omitted. If you configure Doxygen with
* <tt>JAVADOC_AUTOBRIEF=YES</tt>, then the first Line of the comment is used
* instead. In this function this would be as if
* @verbatim @brief Brief can be omitted. @endverbatim
* was used instead.
*/
BOXEXPORT void f_co_theLastOne(void);

#endif /* _CO_DOCUMENT_H */

/****************************************************************************/
