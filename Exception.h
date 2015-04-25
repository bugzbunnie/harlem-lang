#define ASSERT_OK if(!OK()){ Dump();  assert(!"smth is wrong (OK func)"); }
#define EXIT ASSERT_OK return true;
#define elif else if

#define CEXCEPTION_PARAMS __FILE__, __LINE__
class CException: std::exception
{

private:

  string what_string;

public:

  CException(const char* file_name_, const int line_,
             string error_name_,
             CException* parent_error_ = NULL)
  {

    what_string += "line - ";
    char line[5];
    itoa(line_, line, 10);
    assert(line);
    what_string += line;

    if(file_name_)
    {

      what_string += " file - ";
      what_string += file_name_;

    }

    if(error_name_.data())
    {

      what_string += " error - ";
      what_string += error_name_;

    }

    if(parent_error_)
    {

      what_string += parent_error_->what();

    }

    ASSERT_OK

  }

  ~CException() throw()
  {

    ASSERT_OK

    what_string.clear();

  }

  bool OK() const
  {

    if(&what_string && what_string.data() && this)
      return true;
    else
      return false;

  }

  bool Dump() const
  {

    cout << "\n---CExceptionDump---\n\n";
    cout << "&what_string = " << &what_string << "\n";
    cout << "\n---CExceptionDump---\n\n";

    return true;

  }

  const char* what() const throw()
  {

    ASSERT_OK
    return what_string.data();

  }

};

class CNoCopybleObject
{

private:

  CNoCopybleObject(const CNoCopybleObject& that);
  const CNoCopybleObject& operator = (const CNoCopybleObject& that);

public:

  CNoCopybleObject()
  {}

};
