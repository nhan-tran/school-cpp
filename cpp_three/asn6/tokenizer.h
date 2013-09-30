

//
// Tokenizing class
//
// Michael Hoffman
//
// File: tokenizer.h
//
//
// Given a string, this class will break it up into
// individual tokens based on whitespace.
//


#ifndef  tokenizer_H
#define  tokenizer_H

#include  <string>

using  namespace  std;


class Tokenizer
{
  public  :

    enum  Error  { alloc_, noToken_ }; 

    Tokenizer( const string  &str );
      //
      // The constructor is used to instantiate the tokenizer
      // for a specific string. The client's string is not
      // modified by this class. Error::alloc_ is thrown if
      // internal memory allocation fails inside the constructor.
      //

    ~Tokenizer();

    string  nextToken()  const;
      //
      // Returns a string with the next token. If there is no
      // next token, the Error::noToken_ exception is thrown.
      //

    bool  done()  const;
      //
      // Returns true if there is not a next token for the string.
      // Returns false if there is.
      //

  private  :

    char  *m_str;

    mutable  string  m_nextTok;

    //
    // Copying and assignment is not supported
    //
    Tokenizer( const Tokenizer & );
    Tokenizer  &operator=( const Tokenizer & );
};


#endif