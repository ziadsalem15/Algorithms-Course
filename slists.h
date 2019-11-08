typedef enum Staff_or_student
{
  staff,// 0
  student, // 1
  neither // 2
} // staff_or_student

// union varibale named extraInfo to add the following info
typedef union ExtraInfo
{
  char *name_of_program;
  char *staff_room_no;
} // extraInfo
// struct person which consists of character pointer name
//and integer age in years
// and next used topoint tonext element in linke dlist
typedef struct person {
  char* name;
  int age;
  Staff_or_student staff_or_student;
  union ExtraInfo extraInfo; 
  struct person *next;
} person;

// insert_start method which put a nw perosn in the req location
person* insert_start(person *p, char *name, int age);

// insert new person at end of list
person* insert_end(person *p, char *name, int age);

// insert_sorted method ued to put new person in ascending order according
// to either name or age
person* insert_sorted(person *p, char *name, int age, int (*compare_people)(person*, person*));
