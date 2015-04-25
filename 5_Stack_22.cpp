#include <TXLib.h>
#include <math.h>
#include <vector>

using std::vector;


#define ASSERT_OK if(!OK()){ Dump();  assert(!"smth is wrong (OK func)"); }


const int MAX_LINE_NUM = 5;

#define CEXCEPTION_PARAMS __FILE__, __LINE__
class CException: std::exception
{

private:

  string what_string;

public:

  CException(const char* file_name_, const int line_,
             const char* error_name_,
             CException* parent_error_ = NULL)
  {

    what_string += "line - ";
    char line[MAX_LINE_NUM] = "";
    itoa(line_, line, 10);
    assert(line);
    what_string += line;

    if(file_name_)
    {

      what_string += " file - ";
      what_string += file_name_;

    }

    if(error_name_)
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

  }

  const char* what() const throw()
  {

    ASSERT_OK
    return what_string.data();

  }

};

////

class CNoCopybleObject
{

private:

  CNoCopybleObject(const CNoCopybleObject& that);
  const CNoCopybleObject& operator = (const CNoCopybleObject& that);

public:

  CNoCopybleObject()
  {}

};


const int SIZE_DELTA = 15;

template <typename T_vect_data>
class CVector: CNoCopybleObject
{

/*Roll_right
  Roll_left  +
  Empty
  Size       +
  Max_size   +
  Clear
  Insert
  Erase      +
  Push_back  +
  Pop_back
  Resize     +*/

private:

  T_vect_data* data;
  int elements_num; //user
  int real_size;    //memory

public:

  int Real_size() const { return real_size; }

  T_vect_data* Data() const { return data; }

  bool PrintData() const
  {

    ASSERT_OK

    cout << "Data:";

    for(int i = 0; i < elements_num; ++i)
    {

      cout << " " << data[i];

    }

    ASSERT_OK
    return true;

  }


  CVector():
    elements_num(0), real_size(SIZE_DELTA)
  {

    data = new T_vect_data[real_size];
    if(!data)
      throw CException(CEXCEPTION_PARAMS, "Îøèáêà äèíàìè÷åñêîãî âûäåëåíèÿ ïàìÿòè â êîíñòðóòîðå (Ô.Ñ.)");

    std::fill_n(data, real_size, 0);

  }

  ~CVector()
  {

    if(data)
      delete[] data;
    real_size = 0;
    elements_num = 0;

  }

  T_vect_data & operator [] (int data_pos)
  {

    //cout << "\ndata_pos = " << data_pos << "\nelements_num = " << elements_num << "\n";
    ASSERT_OK
    assert(data_pos < elements_num);
    return data[data_pos];

  }


  T_vect_data Pop()
  {

    ASSERT_OK

    elements_num--;
    int ret_el = data[elements_num];
    //cout << "ret_el = " << ret_el << "\n";
    data[elements_num] = 0;

    ASSERT_OK
    return ret_el;

  }

  bool Push_back(int new_element)
  {

    //cout << "Pushback in stack\n";
    //cout << "El_nums - push_back - vetor " << elements_num << "\n\n";

    //Dump();

    //cout << "Dump end\n";
    //cout << "elements num before []  = " << elements_num << "\n";
    ASSERT_OK
    data[elements_num] = new_element;
    ++elements_num;

    if(elements_num == real_size)
      Resize();

    ASSERT_OK

  }

  bool Resize()
  {

    //cout << "Resize\n";

    ASSERT_OK

    real_size = elements_num + SIZE_DELTA;
    T_vect_data* new_data = new T_vect_data[real_size];

    if(!new_data)
    {

      throw CException(CEXCEPTION_PARAMS, "Îøèáêà äèíàìè÷åñêîãî âûäåëåíèÿ ïàìÿòè (Ô.Ñ.)");
      return false;

    }

    for(int i = 0; i < real_size; ++i)
    {

      if(i < elements_num)
        new_data[i] = data[i];
      else
        new_data[i] = 0;

    }

    if(data)
      delete[] data;
    data = new_data;

    new_data = NULL;

    ASSERT_OK

    return true;

  }


  const bool OK() const
  {

    if(elements_num >= 0 && real_size >= 0 && &data && this)
      return true;
    else
      return false;

  }

  bool Dump() const
  {

    cout << "Dump function.\n\nClass CVector.\n";

    cout << "  ";
    PrintData();

    cout << "\nVector Size     = " << real_size << "\n";
    cout << "Function return values:";
    cout << "  OK  -  " << OK() << "\n";

  }

};

////

template <typename T_vect_data>
class CStack
{

private:

  CVector<T_vect_data> data;
  int count;

public:

  CStack():
    count(0)
  {}

  const bool OK() const
  {

    if(count >= 0 && data.OK() && this)
      return true;
    else
      return false;

  }

  bool PrintData() const
  {

    ASSERT_OK
    data.PrintData();
    ASSERT_OK
    return true;

  }

  bool Dump() const
  {

    cout << "\n" << __LINE__ << "\nStack dump function, \nOK() = " << OK() << "\ncount = " << count
         << "\ndata.OK = " << data.OK() << "\n";
    data.PrintData();
    cout << "\nStack Dump Function --- END.\n\n";
    return true;

  }

  bool Push(T_vect_data new_el)
  {

    ASSERT_OK

    //cout << "count = " << count << "\n";
    data.Push_back(new_el);
    ++count;
    //cout << "push - count + 1, = " << count << "\n";

    ASSERT_OK

    return true;

  }

  T_vect_data Pop()
  {

    //cout << "POP start\n";
    ASSERT_OK
    //assert(count);

    //cout << " count = " << count << "\n";
    --count;

    //cout << "POP end\n";
    ASSERT_OK

    return data.Pop();

  }

};


////

#define MARKER 100

const int REG_NUM = 4;

template <typename T_covering>
class CChecker
{

private:

  T_covering* obj;

public:

  CChecker(const T_covering* obj_):
    obj((T_covering*)obj_)
  {

    assert(obj);
    assert(obj->OK());

  }

  ~CChecker()
  {

    assert(obj);
    assert(obj->OK());

  }

};

#define CHECK ASSERT_OK

class CCPU: CNoCopybleObject
{

private:

  int commands_num;
  vector <int> commands;
  int cur_com_pos;

  CStack <double> stack;
  CStack <int> ret_addresses;

  //int markers_addresses[MARK_NUM];
  std::map <int, int> markers_addresses;
  double registers[REG_NUM];

  CChecker <CCPU> checker;

public:

  ////

  bool OK() const
  {

    if(&commands &&  &stack && &registers && &markers_addresses && stack.OK() && this)
      return true;
    else
      return false;

  }

  bool Dump() const
  {

    cout << "\n---CPU_DUMP---\n\n"
         << "commands_num       = " << commands_num << "\n"
         << "&commands          = " << &commands    << "\n"
         << "&stack             = " << &stack       << "\n"
         << "&markers_addresses = " << &markers_addresses << "\n"
         << "&registers         = " << &registers   << "\n"
         << "&checker           = " << &checker     << "\n"
         << "\n---CPU_DUMP---\n\n";

  }

  CCPU(const int& commands_num_, const int* commands_):
    checker(this), stack(), ret_addresses(), markers_addresses(), registers()
  {

    //cout << "CPU CONSTRUCT --- 1\n\n";
    //cout << sizeof(registers) << "\n";

    //markers_addresses = new int;
    //registers = new double;

    cur_com_pos = 0;
    commands_num = commands_num_;
    assert(commands_num);

    std::fill_n(registers, REG_NUM, 0);

    CHECK

    assert(commands_);

    $y

    int mark_size = 0;

    for(int j = 0; j < commands_num; j++)
    {

  //    cout << "j = " << j << "\n";
  //    cout << "commands[j] = " << commands[j] << "\n";

      if(commands_[j] >= MARKER)
      {

        //cout << "  commands[j] = " << commands[j] % MARKER << "\n";
        //cout << "in iF\n";

        //cout << "MARKER = "<< j << "\n";
        assert(&markers_addresses);
        markers_addresses[commands_[j] % MARKER] = j - mark_size;
        mark_size++;
        assert(j >= 0 && j < commands_num);

        //cout << "markers_addresses[commands[j + 1] % MARKER] = " << markers_addresses[commands[j + 1] % MARKER] << "\n";

      }
      else
      {

        commands.push_back(commands_[j]);

      }

    }

    assert(commands.data());
    commands_num = commands.size();
    assert(commands_num);

    /*for(int i = 0; i < commands_num; ++i)
      cout << commands[i] << " ";

    cout << " Markers: ";

    int size = markers_addresses.size();
    for(int i = 0; i < size; ++i)
      cout << markers_addresses[i] << " ";

    cout << "\n\n";*/

    CHECK

    //cout << "CPU CONSTRUCT --- 2\n\n";

  }


  bool in(){ CHECK cin >> registers[commands[cur_com_pos + 1] % MARKER]; CHECK return true; }
  bool out()
  {

    CHECK
    $r //cout << "OUT\n";
    //cout << "commands[cur_com_pos += 1] % MARKER = " << commands[cur_com_pos += 1] % MARKER << "\n";
    //cout << registers[commands[cur_com_pos += 1] % MARKER] << "\n\n"; $d


    int num = stack.Pop();
    cout << num << "\n";
    stack.Push(num); $d
    //getch();

    CHECK
    return true;

  }

  bool push()
  {

    CHECK

    //cout << "push\n";

    double num = -1;
    num = commands[cur_com_pos + 1];

//    cout << "num = " << num << "\n";

    return stack.Push(num);

  }

  bool pop()
  {

    //cout << "pop\n";
    CHECK
    //cout << "commands[cur_pos] = " << commands[cur_com_pos + 1] << "\n";
    assert(commands[cur_com_pos + 1] < REG_NUM && commands[cur_com_pos + 1] >= 0);
    registers[commands[cur_com_pos + 1]] = stack.Pop();
    CHECK
    return true;

  }

  bool pushr()
  {

    //cout << "pushr\n";
    CHECK

    //cout << cur_com_pos + 1 << "\n";
    //cout << commands[cur_com_pos] << "\n";
    //cout << registers[commands[cur_com_pos + 1]] << "\n";

    stack.Push(registers[commands[cur_com_pos + 1]]);

    //cout << "new_cur_com_pos " << cur_com_pos << "\n";

    CHECK
    return true;

  }

  bool sqroot(){ CHECK return stack.Push(sqrt(stack.Pop())); }

  bool add(){ CHECK /*cout << "add\n";*/ return stack.Push(stack.Pop() + stack.Pop()); }
  bool sub(){ CHECK return stack.Push(stack.Pop() - stack.Pop()); }
  bool mul(){ CHECK return stack.Push(stack.Pop() * stack.Pop()); }
  bool div(){ CHECK return stack.Push(stack.Pop() / stack.Pop()); }
  bool end(){ CHECK return false; }

  bool dup()
  {

    CHECK
    //cout << "dup\n";
    double num = stack.Pop();
    stack.Push(num);
    stack.Push(num);
    CHECK
    return true;

  }

  bool jump()
  {

    CHECK

    //cout << "jump\n";
    ret_addresses.Push(cur_com_pos);

    int mark = commands[cur_com_pos + 1];
    assert(mark < commands_num && mark >= 0);
    cur_com_pos = markers_addresses[mark] - 2 ;
    assert(cur_com_pos >= 0 && cur_com_pos < commands_num);

    //cout << "cur_com_pos after jump = " << cur_com_pos << "\n\n";

    CHECK
    return true;

  }

  bool call()
  {

    CHECK
    //cout << "call\n";
    jump();
    CHECK
    return true;

  }

  bool ret()
  {

    CHECK
    //cout << "ret\n";
    cur_com_pos = ret_addresses.Pop() + 1;
    //cout << "cur_com_pos after ret = " << cur_com_pos << "\n";
    CHECK
    return true;

  }

  bool jbe()
  {

    CHECK
    //cout << "jbe\n";

    int num1 = stack.Pop(),
        num2 = stack.Pop();

    //cout << "num1 = " << num1 << ", num2 = " << num2 << "\n";

    if(num1 <= num2)
    {

      jump();

    }

    CHECK
    return true;

  }

  bool jae()
  {

    CHECK
    //cout << "jae\n";

    int num1 = stack.Pop(),
        num2 = stack.Pop();

    //cout << "num1 = " << num1 << ", num2 = " << num2 << "\n";

    if(num1 >= num2)
    {

      jump();

    }

    CHECK
    return true;

  }

  bool jne()
  {

    CHECK
    //cout << "jne\n";

    int num1 = stack.Pop(),
        num2 = stack.Pop();

    //cout << "num1 = " << num1 << ", num2 = " << num2 << "\n";

    if(num1 != num2)
    {

      jump();

    }

    CHECK
    return true;

  }

  bool ja()
  {

    CHECK
    //cout << "ja\n";

    int num1 = stack.Pop(),
        num2 = stack.Pop();

    //cout << "num1 = " << num1 << ", num2 = " << num2 << "\n";

    if(num1 > num2)
    {

      jump();

    }

    CHECK
    return true;

  }

  bool jb()
  {

    CHECK
    //cout << "jb\n";

    int num1 = stack.Pop(),
        num2 = stack.Pop();

    //cout << "num1 = " << num1 << ", num2 = " << num2 << "\n";

    if(num1 < num2)
    {

      jump();

    }

    CHECK
    return true;

  }

  bool je()
  {

    CHECK
    //cout << "je\n";

    int num1 = stack.Pop(),
        num2 = stack.Pop();

    //cout << "num1 = " << num1 << ", num2 = " << num2 << "\n";

    if(num1 == num2)
    {

      jump();

    }

    CHECK
    return true;

  }


  double Run();

};


struct SCommand
{

  const char* name;
  const int params_num;
  const int asm_code;
  bool (CCPU::*CommandFunc)();

};


const int MAX_COMMAND_NAME_SIZE = 7;

/*static*/ const int COMMANDS_NUM = 21;
       const SCommand COMMANDS[COMMANDS_NUM] = {{"push",  1, 68,  &CCPU::push},
                                                {"pushr", 1, 13,  &CCPU::pushr},
                                                {"pop",   1, 10,  &CCPU::pop},
                                                {"in",    1, 8,   &CCPU::in},
                                                {"out",   0, 9 ,  &CCPU::out},
                                                {"sqrt",  0, 11,  &CCPU::sqroot},
                                                {"add",   0, 1,   &CCPU::add},
                                                {"sub",   0, 2,   &CCPU::sub},
                                                {"mul",   0, 3,   &CCPU::mul},
                                                {"div",   0, 4,   &CCPU::div},
                                                {"end",   0, 0,   &CCPU::end},
                                                {"dup",   0, 20,  &CCPU::dup},
                                                {"ret",   0, 7,   &CCPU::ret},
                                                {"jmp",   1, 5,   &CCPU::jump},
                                                {"call",  1, 6,   &CCPU::call},
                                                {"jae",   1, 31,  &CCPU::jae},
                                                {"jbe",   1, 32,  &CCPU::jbe},
                                                {"jne",   1, 33,  &CCPU::jne},
                                                {"ja",    1, 34,  &CCPU::ja},
                                                {"jb",    1, 35,  &CCPU::jb},
                                                {"je",    1, 36,  &CCPU::je}};


double CCPU::Run()
{

  //cout << "markers_addresses[0] = " << markers_addresses[0] << "\n";
  $d

  CHECK

  for(cur_com_pos = 0; ; ++cur_com_pos)
  {

    int com_asm_code = -1;

    CHECK

    com_asm_code = commands[cur_com_pos];
    assert(com_asm_code != -1); //èëè îøèáêà íàïèñàíèå àñì. êîäà

    bool not_end_or_err = true;

    for(int j = 0; j < COMMANDS_NUM; ++j)
    {

      if(com_asm_code == COMMANDS[j].asm_code)
      {

        assert(&COMMANDS[j]);
        assert(&COMMANDS[j].CommandFunc);
        not_end_or_err = (this->*COMMANDS[j].CommandFunc)();
        cur_com_pos += COMMANDS[j].params_num;
        break;

      }

    }

    if(!not_end_or_err)
    {

      return stack.Pop();

    }

  }

  CHECK

  return true;

}


bool Tran2ASM(const char* file_name, vector <int>* commands)
{

  FILE* file = fopen(file_name, "r");
  assert(file);
  rewind(file);

  string num;

  for(int i = 0; ; ++i)
  {


    char com_name[MAX_COMMAND_NAME_SIZE];
    int success = fscanf(file, "%s ", &com_name);

    if(com_name[0] == ':') // MARKER
    {

      int new_mark_num = atoi(&com_name[1]);
      assert(new_mark_num < MARKER);
      commands->push_back(new_mark_num + MARKER);

    }
    else for(int j = 0; j < COMMANDS_NUM; ++j)
    {

      assert(com_name);
      bool not_equal = !strcmp(com_name, COMMANDS[j].name);

      if(not_equal)
      {

        commands->push_back(COMMANDS[j].asm_code);

        for(int par_num = 0; par_num < COMMANDS[j].params_num; ++par_num)
        {

          num.clear();
          fscanf(file, "%s ", (num.data()));

          if(num[0] == ':')
            commands->push_back(atoi(&num[1]));
          else
            commands->push_back(atoi(num.data()));

        }

      }


    }

    if(feof(file))
      break;

  }

  return true;

}


int main()
{

  try
  {

    vector <int> commands;
    const char* file_name = "asm.txt";
    Tran2ASM(file_name, &commands);

    $g
    cout << "Commands, translated to assembler code\n";
    int size = commands.size();
    for(int i = 0; i < size; ++i)
      cout << commands[i] << " ";

    cout << "\n\n";
    $d

    //cout << "cpu\n";
    CCPU cpu(size, commands.data());
    //cout << "run\n";

    $b
    cout << "Result:\n";
    $d

    cpu.Run();

    //cout << "--END--\n";

/*
    for(double x = -50; x < +50; x += 0.1)
    {

      //getch();

      //cout << "x = " << x << "\n";
      cpu.SetAX(x);
      //cout << "RUN\n";
      double y = cpu.Run();
      //cout << "y = " << y << "\n";

      //txSetFillColor(TX_RED);
      //txSetColor(TX_RED);
      //txCircle(400 + x, 300 - y / 10, 2);

      cout << "forend\n\n";

    }

//    cout << "END FOR\n";
*/

  }

  catch(CException err)
  {

    cout << err.what() << "\n";

  }

  catch(...)
  {

    cout << "\n\ncatch(...) fell, so work harder, i need more catch blocks!!!\n\nend\n\n";

  }

  //cout << "\n\n---END---\n\n";

  return false;

}
