/*
   Practical C++ programming - O'Reilly - Steve Oualline - pp 236,237
   demo that REAL C++ code can be used
   Tuesday October  18   2016

  ideas for use of this include : array of LED pins
  create arrays for each pattern - i.e. will be list of Integers where list will be different lengths

*/
const int MAX = 10;
const int STACK_SIZE = 100;

/*
   This class structure added to check class compilation in Arduino
   page 201 of book above

*/
class stack {
  private:
    int count ;
    int data[STACK_SIZE];
  public:
    void init(void);
    void push (const int item);
    int pop(void);
};
inline void stack::init(void)
{
  count = 0;
}

inline void stack::push(const int item)
{
  data[count] = item;
  ++count;
}

inline int stack::pop(void)
{
  --count;
  return (data[count]);
}


void setup() {
  // put your setup code here, to run once: code that would be in main() is here and
  // the loop() is left untouched to compile but executing needs slightly more thought

  int result;

  int array[MAX];
  int arrayE[MAX - 3]  {3, 1, 6, 8, 5   }; // different name, different length
  // trouble is : no easy way to determine the length of array
  // a trick is to use 0 as end-point and test for end-point before further operations

  init_array_1(array);
  init_array_1(&array[0]);

  init_array_2(array);
  stack a_stack;
  a_stack.init();
  a_stack.push(1);
  result = a_stack.pop();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void init_array_1(int data[])
{
  int index;

  for (index = 0; index < MAX; ++index)
    data[index] = 0;

}

void init_array_2(int *data_ptr)
{
  int index;

  for (index = 0; index < MAX; ++index)
    *(data_ptr + index) = 0;

}


