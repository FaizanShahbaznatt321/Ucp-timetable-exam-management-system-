//Project: UCP TIMETABLE & EXAM MANAGEMENT SYSTEM
//COURSE : PROGRAMMING FUNDAMENTALS
//LANGUAGE: C++ CONSOLE LANGUAGE
//GROUP MEMBERS: GRoup of 3 MEMBERS
//NAME of member:Faizan SHahbaz Natt(0932),Sameer Ahmad(0625),Saif-ul-Islam(0639)

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
                                                                    //~~~~~~~Prototype-Part~~~~~~~~~~//
//utility parameters
void printdoubleline();
void printline();
int checkvalidation(const char* prompt, int lo, int hi);
void checkvalidationarr(const char* prompt, char* out, int maxLen);
bool comp(const char* ch1, const char* ch2);
void safecopy(char* dest, const char* src, int maxLen);

// Timetable
void displayAllTimetable(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount);
void growTT(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int ttCount, int& ttCap, int newCap, int Column_size);
void addCourse(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size);
void deleteCourse(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size, int initial_cap);
void updateCourse(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount, int Column_size);
void searchByCode(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount, int Column_size);
void searchByInstructor(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount, int Column_size);


// Exam Management system
void displayAllExams(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount);
void addExam(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size);
void growEX(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int exCount, int& exCap, int newCap, int Column_size);
void deleteExam(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size, int initial_cap);
void updateExam(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount, int Column_size);
void filterExamByDate(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount, int Column_size);
void filterExamByHall(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount, int Column_size);


//  clash detection prototype
void detectRoomClash(char** ttcode, char** ttcourse, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount);
void detectInstructorClash(char** ttcode, char** ttinstructor, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount);


// file I/O prototype
void saveTimetable(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount);
void saveExams(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount);
void loadDefaultTimetable(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size);
void loadDefaultExams(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size);
void loadTimetable(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size);
void loadExams(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size);

//menu Prototypes
void timetableMenu(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size, int initial_cap);
void examMenu(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size, int initial_cap);
void clashMenu(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount);
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

                                                         //~~~~~~~main function~~~~~~~//
int main()
{
    //constant size 
    const int initial_cap = 5;//at initially only 5 students records are able to store 
    const int Column_size = 50;//we used fixed column size for all arrays;

    //local variable
    int choice;
    int    ttCount = 0;
    int    ttCap = initial_cap;
    int  exCount = 0;
    int  exCap = initial_cap;

    //variables require for timetable
    char** ttcode = nullptr;
    char** ttcourse = nullptr;
    char** ttinstructor = nullptr;
    char** ttroom = nullptr;
    int* ttday = nullptr;
    int* ttStartTime = nullptr;
    int* ttEndTime = nullptr;

    //allocate array to timetable pointers
    ttcode = new char* [initial_cap];
    ttcourse = new char* [initial_cap];
    ttinstructor = new char* [initial_cap];
    ttroom = new char* [initial_cap];
    for (int i = 0; i < initial_cap; i++)
    {
        ttcode[i] = new char[Column_size];
        ttcourse[i] = new char[Column_size];
        ttinstructor[i] = new char[Column_size];
        ttroom[i] = new char[Column_size];
    }
    ttday = new int[initial_cap];
    ttStartTime = new int[initial_cap];
    ttEndTime = new int[initial_cap];


    //variable require for exam
    char** excode = nullptr;
    char** EXhall = nullptr;
    int* exdate = nullptr;
    int* exStartTime = nullptr;
    int* exEndTime = nullptr;

    //allocate array to exam pointers
    excode = new char* [initial_cap];
    EXhall = new char* [initial_cap];
    for (int i = 0; i < initial_cap; i++)
    {
        excode[i] = new char[Column_size];
        EXhall[i] = new char[Column_size];
    }
    exdate = new int[initial_cap];
    exStartTime = new int[initial_cap];
    exEndTime = new int[initial_cap];

    //loading data
    cout << "~~~~~loading data~~~~~~~~~~" << endl;
    loadTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, Column_size);
    loadExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, Column_size);
    printline();


    //menu
    do
    {
        printdoubleline();
        cout << "UCP TIMETABLE & EXAM MANAGEMENT SYSTEM" << endl;
        printdoubleline();
        cout << endl;
        cout << "  1. Timetable Management" << endl;
        cout << "  2. Exam Management" << endl;
        cout << "  3. Clash Detection" << endl;
        cout << "  4. Save Data" << endl;
        cout << "  0. Save & Exit" << endl;

        //input validation function
        choice = checkvalidation("Choose from menu (0-4):", 0, 4);

        //ending line 
        printline();

        //
        if (choice == 1)
        {
            timetableMenu(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, Column_size, initial_cap);
        }
        else if (choice == 2)
        {
            examMenu(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, Column_size, initial_cap);
        }
        else if (choice == 3)
        {
            clashMenu(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount);

        }
        else if (choice == 4)
        {
            saveTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount);
            saveExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount);
        }
        else if (choice == 0)
        {
            cout << "!_saving your records before exist_!" << endl;
            saveTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount);
            saveExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount);

        }

    } while (choice != 0);

    //free all allocated pointer of timetable 
    for (int i = 0; i < ttCap; i++)
    {
        delete[] ttcode[i];
        delete[] ttcourse[i];
        delete[] ttinstructor[i];
        delete[] ttroom[i];
    }
    delete[] ttcode;
    delete[] ttcourse;
    delete[] ttinstructor;
    delete[] ttroom;
    delete[] ttday;
    delete[] ttStartTime;
    delete[] ttEndTime;
    ttcode = nullptr;
    ttcourse = nullptr;
    ttinstructor = nullptr;
    ttroom = nullptr;
    ttday = nullptr;
    ttStartTime = nullptr;
    ttEndTime = nullptr;

    //free all allocated pointer of exam
    for (int i = 0; i < exCap; i++)
    {
        delete[] excode[i];
        delete[] EXhall[i];
    }
    delete[] excode;
    delete[] EXhall;
    delete[] exdate;
    delete[] exStartTime;
    delete[] exEndTime;
    excode = nullptr;
    EXhall = nullptr;
    exdate = nullptr;
    exStartTime = nullptr;
    exEndTime = nullptr;

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------//

                                             //~~~~~~Functon-part~~~~~~//

//=====================
//utility functions
//=====================

//print line
void printdoubleline()
{
    for (int i = 0; i < 50; i++)
    {
        cout << "=";
    }
    cout << endl;
}
void printline()
{
    for (int i = 0; i < 50; i++)
    {
        cout << "-";
    }
    cout << endl;
}

//check the validation of input 
int checkvalidation(const char* prompt, int lo, int hi)
{
    int val;
    while (true)
    {
        cout << prompt;
        cin >> val;
        if (!cin.fail() && val >= lo && val <= hi)
        {
            cin.ignore(1000, '\n');
            return val;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "  ! Enter a number between " << lo << " and " << hi << ".\n";
    }
}
void checkvalidationarr(const char* prompt, char* out, int maxLen)
{
    while (true)
    {
        cout << prompt;
        cin.getline(out, maxLen);
        int start = 0;
        while (out[start] == ' ' || out[start] == '\t')
        {
            start++;
        }
        if (start > 0)
        {
            int i = 0;
            while (out[start + i])
            {
                out[i] = out[start + i];
                i++;
            }
            out[i] = '\0';
        }
        if (strlen(out) > 0)
        {
            return;
        }
        cout << "Input cannot be empty." << endl;
    }
}

//course code already exist 
bool codeExistsTT(char** codes, int count, const char* code)
{
    for (int i = 0; i < count; i++)
    {
        if (comp(*(codes + i), code))
        {
            return true;
        }
    }
    return false;
}


//functions for time and day management
const char* dayName(int d)
{
    switch (d)
    {
    case 0:
        return "Sunday";
    case 1:
        return "Monday";
    case 2:
        return "Tuesday";
    case 3:
        return "Wednesday";
    case 4:
        return "Thursday";
    case 5:
        return "Friday";
    case 6:
        return "Saturday";
    default:
        return "Unknown";
    }
}

void printTime(int t)
{
    if (t < 0 || t > 2359)
    {
        cout << "??:??";
        return;
    }
    cout << t / 100 << ":";
    int mins = t % 100;
    if (mins < 10)
    {
        cout << "0";
    }
    cout << mins;
}

bool timesOverlap(int s1, int e1, int s2, int e2)
{
    if (s1 < e2 && s2 < e1)
    {
        return true;
    }
    return false;
}
bool validDate(int d)
{
    int y = d / 10000;
    int m = (d / 100) % 100;
    int day = d % 100;
    if (m < 1 || m > 12 || day < 1 || day > 31)
    {
        return false;
    }
    if (y < 2000 || y > 2100)
    {
        return false;
    }
    return true;
}

//compare two arrays
bool comp(const char* ch1, const char* ch2)
{
    int i = 0;
    int len1 = strlen(ch1);
    int len2 = strlen(ch2);
    if (len1 != len2)
    {
        return false;
    }
    while (i < len1)
    {
        char temp1 = ch1[i];
        char  temp2 = ch2[i];
        if (temp1 >= 'A' && temp1 <= 'Z')
        {
            temp1 += 32;
        }
        if (temp2 >= 'A' && temp2 <= 'Z')
        {
            temp2 += 32;
        }
        if (temp1 != temp2)
        {
            return false;
        }
        i++;
    }
    return true;
}

//safe copy
void safecopy(char* dest, const char* src, int maxLen)
{
    int i = 0;
    while (i < maxLen - 1 && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
//-----------------------------------------------------------------------------------------------------------------------------------------------//


//===============
//Menu Functions
//===============

//timetable menu
void timetableMenu(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size, int initial_cap)
{
    int ch;
    do
    {
        printdoubleline();
        cout << "UCP TIMETABLE " << endl;
        printdoubleline();
        cout << endl;
        cout << "  1. Display All Courses" << endl;
        cout << "  2. Add Course" << endl;
        cout << "  3. Delete Course" << endl;
        cout << "  4. Update Course" << endl;
        cout << "  5. Search by Code" << endl;
        cout << "  6. Search by Instructor" << endl;
        cout << "  0. Back" << endl;
        ch = checkvalidation("Choose from menu (0-6):", 0, 6);
        if (ch == 1)
        {
            displayAllTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount);
        }
        else if (ch == 2)
        {
            addCourse(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, Column_size);
        }
        else if (ch == 3)
        {
            deleteCourse(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, Column_size, initial_cap);
        }
        else if (ch == 4)
        {
            updateCourse(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, Column_size);
        }
        else if (ch == 5)
        {
            searchByCode(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, Column_size);
        }
        else if (ch == 6)
        {
            searchByInstructor(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, Column_size);
        }
    } while (ch != 0);
}

//exam menu
void examMenu(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size, int initial_cap)
{
    int ch;
    do
    {
        printdoubleline();
        cout << "Exam Management System " << endl;
        printdoubleline();
        cout << endl;
        cout << "  1. Display All Exams" << endl;
        cout << "  2. Add Exam" << endl;
        cout << "  3. Delete Exam" << endl;
        cout << "  4. Update Exam" << endl;
        cout << "  5. Filter by Date" << endl;
        cout << "  6. Filter by Hall" << endl;
        cout << "  0. Back" << endl;
        ch = checkvalidation("Choose from menu (0-6):", 0, 6);
        if (ch == 1)
        {
            displayAllExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount);
        }
        else if (ch == 2)
        {
            addExam(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, Column_size);
        }
        else if (ch == 3)
        {
            deleteExam(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, Column_size, initial_cap);
        }
        else if (ch == 4)
        {
            updateExam(excode, EXhall, exdate, exStartTime, exEndTime, exCount, Column_size);
        }
        else if (ch == 5)
        {
            filterExamByDate(excode, EXhall, exdate, exStartTime, exEndTime, exCount, Column_size);
        }
        else if (ch == 6)
        {
            filterExamByHall(excode, EXhall, exdate, exStartTime, exEndTime, exCount, Column_size);
        }

    } while (ch != 0);
}

//clash menu 
void clashMenu(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount)
{
    int ch;
    do
    {
        printdoubleline();
        cout << "Clash Detection" << endl;
        printdoubleline();
        cout << "  1. Room Clash Detection" << endl;
        cout << "  2. Instructor Clash Detection" << endl;
        cout << "  0. Back" << endl;
        ch = checkvalidation("Choose from menu (0-2):", 0, 2);
        if (ch == 1)
        {
            detectRoomClash(ttcode, ttcourse, ttroom, ttday, ttStartTime, ttEndTime, ttCount);


        }
        else if (ch == 2)
        {
            detectInstructorClash(ttcode, ttinstructor, ttday, ttStartTime, ttEndTime, ttCount);
        }
    } while (ch != 0);
}
//------------------------------------------------------------------------------------------------------------------------------------------//


//=============
// Timetable 
//=============

//display menu
void displayAllTimetable(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount)
{
    if (ttCount == 0)
    {
        cout << "  No timetable entries found." << endl;
        return;
    }
    printdoubleline();
    cout << "  FULL TIMETABLE  (" << ttCount << " courses)\n";
    printdoubleline();
    // pointer arithmetic as required
    for (int i = 0; i < ttCount; i++)
    {
        cout << "  [" << i + 1 << "] " << *(ttcode + i) << " | " << *(ttcourse + i) << endl;
        cout << "      Instructor : " << *(ttinstructor + i) << endl;
        cout << "      Room       : " << *(ttroom + i) << endl;
        cout << "      Day        : " << dayName(*(ttday + i)) << endl;//display the day with respect to the input number
        cout << "      Time       : ";
        printTime(*(ttStartTime + i));//checkpoint for display accurate time
        cout << " - ";
        printTime(*(ttEndTime + i)); //checkpoints for display accurate time
        cout << endl;
        printline();
    }
}

//grow timetable
void growTT(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int ttCount, int& ttCap, int newCap, int Column_size)
{
    // Allocate new arrays
    char** nc = new char* [newCap];
    char** nn = new char* [newCap];
    char** ni = new char* [newCap];
    char** nr = new char* [newCap];
    for (int i = 0; i < newCap; i++)
    {
        nc[i] = new char[Column_size];
        nn[i] = new char[Column_size];
        ni[i] = new char[Column_size];
        nr[i] = new char[Column_size];
    }
    int* nd = new int[newCap];
    int* ns = new int[newCap];
    int* ne = new int[newCap];

    // Copy existing data
    int copyCount;
    if (ttCount < newCap)
    {
        copyCount = ttCount;
    }
    else
    {
       copyCount = newCap;
    }
    for (int i = 0; i < copyCount; i++)
    {
        safecopy(nc[i], ttcode[i],Column_size);
        safecopy(nn[i], ttcourse[i],Column_size);
        safecopy(ni[i], ttinstructor[i],Column_size);
        safecopy(nr[i], ttroom[i],Column_size);
        nd[i] = ttday[i];
        ns[i] = ttStartTime[i];
        ne[i] = ttEndTime[i];
    }

    // Free old arrays
    for (int i = 0; i < ttCap; i++)
    {
        delete[] ttcode[i];  
        delete[] ttcourse[i];
        delete[] ttinstructor[i];
        delete[] ttroom[i];
    }
    delete[] ttcode;  
    delete[] ttcourse;
    delete[] ttinstructor;
    delete[] ttroom;
    delete[] ttday;  
    delete[] ttStartTime;
    delete[] ttEndTime;

    ttcode = nc; 
    ttcourse = nn;
    ttinstructor = ni;  
    ttroom = nr;
    ttday = nd;  
    ttStartTime = ns; 
    ttEndTime = ne;
    ttCap = newCap;
}

//add course 
void addCourse(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size)
{
    // Auto-grow
    if (ttCount >= ttCap)
    {
        cout << "Capacity " << ttCap << " -> " << ttCap * 2 << "\n";
        growTT(ttcode,ttcourse,ttinstructor,ttroom,ttday,ttStartTime,ttEndTime,ttCount,ttCap,ttCap * 2, Column_size);
    }

    char* temp = new char[Column_size];

    // Duplicate-free course code
    while (true)
    {
       checkvalidationarr("  Course Code   : ", temp, Column_size);
       if (!codeExistsTT(ttcode, ttCount, temp))
       {
           break;
       }
        cout << "  Course code \"" <<temp << "\" already exists."<<endl;
    }
    safecopy(*(ttcode + ttCount), temp, Column_size);

    checkvalidationarr("  Course Name   : ", temp, Column_size);
    safecopy(*(ttcourse + ttCount),temp, Column_size);

    checkvalidationarr("  Instructor    : ", temp,Column_size);
    safecopy(*(ttinstructor + ttCount), temp, Column_size);

    checkvalidationarr("  Room          : ",temp,Column_size);
    safecopy(*(ttroom + ttCount),temp,Column_size);

    *(ttday + ttCount) =checkvalidation("  Day (0=Sun 1=Mon .. 6=Sat): ", 0, 6);

    int s, e;
    while (true) //checkpoint
    {
        s = checkvalidation("  Start Time (e.g. 800): ", 0, 2359);
        e = checkvalidation("  End   Time (e.g. 930): ", 0, 2359);
        if (e > s)
        {
            break;
        }
        cout << " End time must be after start time."<<endl;
    }
    *(ttStartTime + ttCount) = s;
    *(ttEndTime + ttCount) = e;
    ttCount++;
    cout << "Course added."<<endl;
    
    delete[] temp;
    temp = nullptr;
}

//delete course (by shrink concept)
void deleteCourse(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size, int initial_cap)
{
    if (ttCount == 0)
    {
        cout << "  No courses to delete." << endl;
        return; 
    }
    displayAllTimetable(ttcode,ttcourse,ttinstructor,ttroom,ttday,ttStartTime,ttEndTime,ttCount);

    int idx = checkvalidation("  Entry number to delete: ", 1, ttCount) - 1;

    // Confirm deletion
    char confirm[10];
    cout << "  Delete \"" << *(ttcode + idx) << "\"? (yes/no): ";
    cin.getline(confirm, 10);
    if (!comp(confirm, "yes"))
    {
        cout << "  Cancelled."<<endl; 
        return;
    }

    // Shift left using pointer arithmetic
    for (int i = idx; i < ttCount - 1; i++)
    {
        safecopy(*(ttcode + i), *(ttcode + i + 1), Column_size);
        safecopy(*(ttcourse + i), *(ttcourse + i + 1), Column_size);
        safecopy(*(ttinstructor + i), *(ttinstructor + i + 1),Column_size);
        safecopy(*(ttroom + i), *(ttroom + i + 1), Column_size);
        *(ttday + i) = *(ttday + i + 1);
        *(ttStartTime + i) = *(ttStartTime + i + 1);
        *(ttEndTime + i) = *(ttEndTime + i + 1);
    }
    ttCount--;

    // Auto-shrink: count < 25% of cap, min cap = INIT_CAP
    if (ttCap > initial_cap && ttCount < ttCap / 4)
    {
        int newCap;
        if (ttCap / 2 < initial_cap)
        {
            newCap = initial_cap;
        }
        else
        {
         newCap = ttCap / 2;
        }
        cout << "Capacity " << ttCap << " - " << newCap <<endl;
        growTT(ttcode,ttcourse,ttinstructor,ttroom,ttday,ttStartTime,ttEndTime,ttCount,ttCap, newCap,Column_size);
    }
    cout << "Course deleted.\n";
}

//update course 
void updateCourse(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount, int Column_size)
{
    if (ttCount == 0)
    {
        cout << "  No courses to update." << endl;
        return;
    }
    displayAllTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount);

    int idx = checkvalidation("  Entry number to update: ", 1, ttCount) - 1; // index of that entry
    printline();
    cout << "  1. Code  2. Name  3. Instructor  4. Room  5. Day   6. Start Time  7. End Time" << endl;
    int ch = checkvalidation("  Field to update: ", 1, 7);
    char* temp = new char[Column_size];
    switch (ch)
    {
    case 1:
        checkvalidationarr("  New Code: ", temp, Column_size);
        safecopy(*(ttcode + idx), temp, Column_size);
        break;
    case 2:
        checkvalidationarr("  New course: ", temp, Column_size);
        safecopy(*(ttcourse + idx), temp, Column_size);
        break;
    case 3:
        checkvalidationarr("  New INstructor: ", temp, Column_size);
        safecopy(*(ttinstructor + idx), temp, Column_size);
        break;
    case 4:
        checkvalidationarr("  New Room: ", temp, Column_size);
        safecopy(*(ttroom + idx), temp, Column_size);
        break;
    case 5:
        *(ttday + idx) = checkvalidation("  New Day (0-6): ", 0, 6);
        break;
    case 6:
    {
        int s;
        while (true)
        {
            s = checkvalidation("  New Start Time: ", 0, 2359);
            if (s < *(ttEndTime + idx))
            {
                break;
            }
            cout << "Start must be before current end ";
            printTime(*(ttEndTime + idx));
            cout << endl;
        }
        *(ttStartTime + idx) = s;
        break;
    }
    case 7:
    {
        int e;
        while (true)
        {
            e = checkvalidation("  New End Time: ", 0, 2359);
            if (e > *(ttStartTime + idx))
            {
                break;
            }
            cout << "  ! End must be after current start ";
            printTime(*(ttStartTime + idx));
            cout << endl;
        }
        *(ttEndTime + idx) = e;
        break;
    }
    }
    cout << "Course updated." << endl;
    delete[] temp;
    temp = nullptr;
}

//search by code 
void searchByCode(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount, int Column_size)
{
    if (ttCount == 0)
    {
        cout << " No entries." << endl;
        return;
    }
    char* temp = new char[Column_size];
    checkvalidationarr("  Course Code to search: ", temp, Column_size);

    bool found = false;
    for (int i = 0; i < ttCount; i++)
    {
        if (comp(*(ttcode + i), temp))
        {
            printline();
            cout << "  " << *(ttcode + i) << " | " << *(ttcourse + i) << endl;
            cout << "  Instructor : " << *(ttinstructor + i) << endl;
            cout << "  Room       : " << *(ttroom + i) << endl;
            cout << "  Day        : " << dayName(*(ttday + i)) << endl;
            cout << "  Time       : ";
            printTime(*(ttStartTime + i)); cout << " - "; printTime(*(ttEndTime + i));
            cout << "\n";
            printline();
            found = true;
        }
    }
    if (!found)
    {
        cout << "  No course found with code " << temp << endl;
    }
    delete[] temp;
    temp = nullptr;
}

//search by instructor name
void searchByInstructor(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount, int Column_size)
{
    if (ttCount == 0)
    {
        cout << "  No entries." << endl;
        return;
    }
    char* temp = new char[Column_size];
    checkvalidationarr("  Instructor name (name only): ", temp, Column_size);
    bool found = false;
    for (int i = 0; i < ttCount; i++)
    {
        if (comp(*(ttinstructor + i), temp))
        {
            printline();
            cout << "  " << *(ttcode + i) << " | " << *(ttcourse + i) << endl;
            cout << "  Instructor : " << *(ttinstructor + i) << endl;
            cout << "  Room       : " << *(ttroom + i) << endl;
            cout << "  Day        : " << dayName(*(ttday + i)) << endl;
            cout << "  Time       : ";
            printTime(*(ttStartTime + i));
            cout << " - ";
            printTime(*(ttEndTime + i));
            cout << "\n";
            found = true;
        }
    }
    if (!found)
    {
        cout << "  No courses found for \"" << temp << "\".\n";
    }
    delete[] temp;
    temp = nullptr;
}


//=========================
// Exam Management system
//=========================

//display exam schedule
void displayAllExams(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount)
{
    if (exCount == 0)
    {
        cout << "  No exam entries found." << endl;
        return;
    }
    printdoubleline();
    cout << "  EXAM SCHEDULE  (" << exCount << " exams)" << endl;
    printdoubleline();
    for (int i = 0; i < exCount; i++)
    {
        int d = *(exdate + i);
        cout << "  [" << i + 1 << "] " << *(excode + i) << " | Hall: " << *(EXhall + i) << endl;
        cout << "      Date  : " << d / 10000 << "-" << (d / 100) % 100 << "-" << d % 100 << endl;
        cout << "      Time  : ";
        printTime(*(exStartTime + i));
        cout << " - "; printTime(*(exEndTime + i));
        cout << endl;
        printline();
    }
}

//add exam 
void addExam(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size)
{
    if (exCount >= exCap)
    {
        cout << "Exam capacity " << exCap << " -> " << exCap * 2 << endl;
        growEX(excode,EXhall,exdate,exStartTime,exEndTime,exCount,exCap,exCap * 2, Column_size);
    }
    char* temp = new char[Column_size];
    checkvalidationarr("  Course Code : ",temp, Column_size);
    safecopy(*(excode + exCount), temp, Column_size);

    checkvalidationarr("  Hall        : ", temp,Column_size);
    safecopy(*(EXhall + exCount), temp,Column_size);

    int date;
    while (true)
    {
        date = checkvalidation("  Date (YYYYMMDD e.g. 20250610): ", 20000101, 21001231);
        if (validDate(date)) break;
        cout << "  ! Invalid date. Check month (01-12) and day (01-31).\n";
    }
    *(exdate + exCount) = date;

    int s, e;
    while (true)
    {
        s = checkvalidation("  Start Time (e.g. 900): ", 0, 2359);
        e = checkvalidation("  End   Time (e.g. 1100): ", 0, 2359);
        if (e > s)
        {
            break;
        }
        cout << "  ! End time must be after start time.\n";
    }
    *(exStartTime + exCount) = s;
    *(exEndTime + exCount) = e;
    exCount++;
    cout << "Exam added.\n";
}

//grow all exam array for new entity
void growEX(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int exCount, int& exCap, int newCap, int Column_size)
{
    char** nc = new char* [newCap];
    char** nh = new char* [newCap];
    for (int i = 0; i < newCap; i++)
    {
        nc[i] = new char[Column_size];
        nh[i] = new char[Column_size];
    }
    int* nd = new int[newCap];
    int* ns = new int[newCap];
    int* ne = new int[newCap];

    int copyCount;
    if (exCount < newCap)
    {
        copyCount = exCount;
    }
    else
    {
        copyCount = newCap;
    }
    for (int i = 0; i < copyCount; i++)
    {
        safecopy(nc[i], excode[i], Column_size);
        safecopy(nh[i], EXhall[i],Column_size);
        nd[i] = exdate[i];
        ns[i] = exStartTime[i];
        ne[i] = exEndTime[i];
    }

    for (int i = 0; i < exCap; i++)
    {
        delete[] excode[i];
        delete[] EXhall[i];
    }
    delete[] excode; 
    delete[] EXhall;
    delete[] exdate; 
    delete[] exStartTime;
    delete[] exEndTime;

    excode = nc; 
    EXhall = nh;
    exdate = nd; 
    exStartTime = ns;
    exEndTime = ne;
    exCap = newCap;
}

//delete exam entity (using auto-shrink concept)
void deleteExam(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size, int initial_cap)
{
    if (exCount == 0)
    {
        cout << "  No exams to delete." << endl;
        return;
    }

    displayAllExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount);
    int idx = checkvalidation("  Entry number to delete: ", 1, exCount) - 1;

    //confirmation for delete
    char confirm[10];
    cout << "  Delete exam for \"" << *(excode + idx) << "\"? (yes/no): ";
    cin.getline(confirm, 10);
    if (!comp(confirm, "yes"))
    {
        cout << "  Cancelled." << endl;
        return;
    }
    //-----------------//
    for (int i = idx; i < exCount - 1; i++)
    {
        safecopy(*(excode + i), *(excode + i + 1), Column_size);
        safecopy(*(EXhall + i), *(EXhall + i + 1), Column_size);
        *(exdate + i) = *(exdate + i + 1);
        *(exStartTime + i) = *(exStartTime + i + 1);
        *(exEndTime + i) = *(exEndTime + i + 1);
    }
    exCount--;

    if (exCap > initial_cap && exCount < exCap / 4)
    {
        int newCap;
        if (exCap / 2 < initial_cap)
        {
            newCap = initial_cap;
        }
        else
        {
            newCap = exCap / 2;
        }
        cout << "Exam capacity " << exCap << " -> " << newCap << "\n";
        growEX(excode,EXhall,exdate,exStartTime,exEndTime,exCount,exCap,newCap,Column_size);
    }
    cout << "Exam deleted."<<endl;
}

//update Exam schedule
void updateExam(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount, int Column_size)
{
    if (exCount == 0)
    {
        cout << "  No exams." << endl;
        return;
    }
    displayAllExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount);

    int idx = checkvalidation("  Entry number to update: ", 1, exCount) - 1;
    cout << "  1. Code  2. Hall  3. Date  4. Start  5. End" << endl;
    int ch = checkvalidation("  Field: ", 1, 5);
    char* buf = new char[Column_size];

    switch (ch)
    {
    case 1:
        checkvalidationarr("  New Code: ", buf, Column_size);
        safecopy(*(excode + idx), buf, Column_size);
        break;
    case 2:
        checkvalidationarr("  New Hall: ", buf, Column_size);
        safecopy(*(EXhall + idx), buf, Column_size);
        break;
    case 3:
    {
        int date;
        while (true)
        {
            date = checkvalidation("  New Date (YYYYMMDD): ", 20000101, 21001231);
            if (validDate(date))
            {
                break;
            }
            cout << "  ! Invalid date.\n";
        }
        *(exdate + idx) = date;
        break;
    }
    case 4:
    {
        int s;
        while (true)
        {
            s = checkvalidation("  New Start Time: ", 0, 2359);
            if (s < *(exEndTime + idx)) break;
            cout << "Start must be before end." << endl;
        }
        *(exStartTime + idx) = s;
        break;
    }
    case 5:
    {
        int e;
        while (true)
        {
            e = checkvalidation("  New End Time: ", 0, 2359);
            if (e > *(exStartTime + idx)) break;
            cout << "  ! End must be after start.\n";
        }
        *(exEndTime + idx) = e;
        break;
    }
    }
    cout << "Exam updated."<<endl;

    delete[] buf;
    buf = nullptr;
}

//filter exam by date
void filterExamByDate(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount, int Column_size)
{
    if (exCount == 0)
    {
        cout << "  No exams." << endl;
        return;
    }
    int date;
    while (true)
    {
        date = checkvalidation("  Filter Date (YYYYMMDD): ", 20000101, 21001231);
        if (validDate(date))
        {
            break;
        }
        cout << "  ! Invalid date."<<endl;
    }

    bool found = false;
    for (int i = 0; i < exCount; i++)
    {
        if (*(exdate + i) == date)
        {
            cout << "  " << *(excode + i) << " | Hall: " << *(EXhall + i) << " | ";
            printTime(*(exStartTime + i));
            cout << " - ";
            printTime(*(exEndTime + i));
            cout << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "  No exams on that date." << endl;
    }
}

//filter exam by hall
void filterExamByHall(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount, int Column_size)
{
    if (exCount == 0)
    {
        cout << " No exams." << endl;
        return;
    }
    char* temp = new char[Column_size];
    checkvalidationarr("  Hall name: ", temp, Column_size);

    // Collect matching indices into a temporary int* results array (as required)
    int* results = new int[exCount];
    int  rCount = 0;
    for (int i = 0; i < exCount; i++)
    {
        if (comp(*(EXhall + i), temp))
        {
            *(results + rCount++) = i;
        }
    }
    if (rCount == 0)
        cout << "  No exams in hall " << temp << endl;
    else
    {
        cout << "  Exams in " << temp << ":" << endl;
        printline();
        for (int r = 0; r < rCount; r++)
        {
            int i = *(results + r);
            cout << "  " << *(excode + i) << " | Date: " << *(exdate + i) << " | ";
            printTime(*(exStartTime + i));
            cout << " - ";
            printTime(*(exEndTime + i));
            cout << "\n";
        }
    }
    delete[] results;
    delete[] temp;
    temp = nullptr;
}
//-------------------------------------------------------------------------------------------------------------------------------//


//==============================
//  clash detection prototype
//==============================

//detect room clash
void detectRoomClash(char** ttcode, char** ttcourse, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount)
{
    if (ttCount < 2)
    {
        cout << "  Not enough entries."<<endl;
        return;
    }

    // Collect clashing index pairs into temporary int* arrays (as required)
    int* clashA = new int[ttCount];
    int* clashB = new int[ttCount];
    int  cCount = 0;

    for (int i = 0; i < ttCount; i++)
    {
        for (int j = i + 1; j < ttCount; j++)
        {
            bool sameRoom = comp(*(ttroom + i), *(ttroom + j));
            bool sameDay = (*(ttday + i) == *(ttday + j));
            bool overlap = timesOverlap(*(ttStartTime + i), *(ttEndTime + i), *(ttStartTime + j), *(ttEndTime + j));
            if (sameRoom && sameDay && overlap)
            {
                *(clashA + cCount) = i;
                *(clashB + cCount) = j;
                cCount++;//check point for clash 
            }
        }
    }

    printdoubleline();
    cout << "  ROOM CLASH REPORT\n";
    printdoubleline();
    if (cCount == 0)
    {
        cout << "  No room clashes detected."<<endl;
    }
    else
    {
        for (int c = 0; c < cCount; c++)
        {
            int i = *(clashA + c), j = *(clashB + c);
            cout << "  *** CLASH ***" << endl;
            cout << "  [A] " << *(ttcode + i) << " (" << *(ttcourse + i) << ")" << "  Room: " << *(ttroom + i) << "  " << dayName(*(ttday + i)) << " ";
            printTime(*(ttStartTime + i)); 
            cout << "-"; 
            printTime(*(ttEndTime + i));
            cout << "\n" << "  [B] " << *(ttcode + j) << " (" << *(ttcourse + j) << ")" << "  Room: " << *(ttroom + j) << "  " << dayName(*(ttday + j)) << " ";
            printTime(*(ttStartTime + j));
            cout << "-";
            printTime(*(ttEndTime + j));
            cout << "\n";
            printline();
        }
    }

    //delete temprary allocatrd memory from pointers 
    delete[] clashA;
    delete[] clashB;
}

//detect instructor clash
void detectInstructorClash(char** ttcode, char** ttinstructor, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount)
{
    if (ttCount < 2)
    {
        cout << "  Not enough entries."<<endl;
        return;
    }

    int* clashA = new int[ttCount];
    int* clashB = new int[ttCount];
    int  cCount = 0;

    for (int i = 0; i < ttCount; i++)
    {
        for (int j = i + 1; j < ttCount; j++)
        {
            bool sameInstr = comp(*(ttinstructor + i), *(ttinstructor + j));
            bool sameDay = (*(ttday + i) == *(ttday + j));
            bool overlap = timesOverlap(*(ttStartTime + i), *(ttEndTime + i), *(ttStartTime + j), *(ttEndTime + j));
            if (sameInstr && sameDay && overlap)
            {
                *(clashA + cCount) = i;
                *(clashB + cCount) = j;
                cCount++;
            }
        }
    }

    printdoubleline();
    cout << "  INSTRUCTOR CLASH REPORT" << endl;
    printdoubleline();
    if (cCount == 0)
    {
        cout << "  No instructor clashes detected." << endl;
    }
    else
    {
        for (int c = 0; c < cCount; c++)
        {
            int i = *(clashA + c), j = *(clashB + c);
            cout << "  *** CLASH ***" << endl;
            cout << "  [A] " << *(ttcode + i) << "  Instructor: " << *(ttinstructor + i) << "  " << dayName(*(ttday + i)) << " ";
            printTime(*(ttStartTime + i));
            cout << "-";
            printTime(*(ttEndTime + i));
            cout << "\n" << "  [B] " << *(ttcode + j) << "  Instructor: " << *(ttinstructor + j) << "  " << dayName(*(ttday + j)) << " ";
            printTime(*(ttStartTime + j)); 
            cout << "-";
            printTime(*(ttEndTime + j));
            cout << "\n";
            printline();
        }
    }
    delete[] clashA;
    delete[] clashB;
}
//---------------------------------------------------------------------------------------------------------------------------------//


//=====================
// file I/O prototype
//=====================

//save timetable
void saveTimetable(char** ttcode, char** ttcourse, char** ttinstructor, char** ttroom, int* ttday, int* ttStartTime, int* ttEndTime, int ttCount)
{
    ofstream fout("timetable.txt");
    if (!fout.is_open())
    {
        cout << "Unable to open timetable file for writing." << endl;
        return;
    }
    fout << ttCount << endl;
    for (int i = 0; i < ttCount; i++)
    {
        // pointer arithmetic as required by assignment
        fout << ttcode[i] << endl;
        fout << ttcourse[i] << endl;
        fout << ttinstructor[i] << endl;
        fout << ttroom[i] << endl;
        fout << ttday[i] << endl;
        fout << ttStartTime[i] << endl;
        fout << ttEndTime[i] << endl;
    }
    fout.close();
    cout << "Timetable saved.\n";
}

//save exam schedule
void saveExams(char** excode, char** EXhall, int* exdate, int* exStartTime, int* exEndTime, int exCount)
{
    ofstream fout("exams.txt");
    if (!fout.is_open())
    {
        cout << "unable to open exams file for writing." << endl;
        return;
    }
    fout << exCount << "\n";
    for (int i = 0; i < exCount; i++)
    {
        fout << excode[i] << endl;
        fout << EXhall[i] << endl;
        fout << exdate[i] << endl;
        fout << exStartTime[i] << endl;
        fout << exEndTime[i] << endl;
    }
    fout.close();
    cout << "Exams record saved." << endl;
}

//load default time table
void loadDefaultTimetable(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size)
{
    char defCodes[5][50] = { "C01","C02","C03","C041","C05" };
    char defNames[5][50] = { "Programming Fundamentals","Essay Writing","Civics","Calculus","Digital Logic Design" };
    char defInstrs[5][50] = { "Sir Ahmed","Sir Adil","Sir Bilal","Sir Ali","Sir Saif" };
    char defRooms[5][50] = { "A-001","A-202","B-004","C-304","A-105" };
    int defDays[5] = { 1,   2,    3,    1,    4 };
    int defStarts[5] = { 800, 930,  1100, 1300, 800 };
    int defEnds[5] = { 930, 1100, 1230, 1430, 930 };

    if (5 > ttCap)
    {
        growTT(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, 10, Column_size);
    }

    for (int i = 0; i < 5; i++)
    {
        //I use pointer arithmetic for display & also use built in c-string strncpy function to copy data from temprary to original
        safecopy(ttcode[i], defCodes[i], Column_size);
        safecopy(*(ttcourse + i), defNames[i], Column_size);
        safecopy(*(ttinstructor + i), defInstrs[i], Column_size);
        safecopy(*(ttroom + i), defRooms[i], Column_size);
        *(ttday + i) = defDays[i];
        *(ttStartTime + i) = defStarts[i];
        *(ttEndTime + i) = defEnds[i];
    }
    ttCount = 5;
    saveTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount);
    cout << "Default timetable created & saved.";
}

//load default exams
void loadDefaultExams(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size)
{
    char defCodes[5][50] = { "C01","C02","C03","C041","C05" };
    char defHalls[5][50] = { "Hall-A","Hall-B","Hall-A","Hall-C","Hall-B" };
    int defDates[5] = { 20250610, 20250611, 20250612, 20250613, 20250614 };
    int defStarts[5] = { 900,  900,  1400, 900,  1400 };
    int defEnds[5] = { 1100, 1100, 1600, 1100, 1600 };

    if (5 > exCap)
    {
        growEX(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, 10, Column_size);
    }

    for (int i = 0; i < 5; i++)
    {
        safecopy(*(excode + i), defCodes[i], Column_size);
        safecopy(*(EXhall + i), defHalls[i], Column_size);
        *(exdate + i) = defDates[i];
        *(exStartTime + i) = defStarts[i];
        *(exEndTime + i) = defEnds[i];
    }
    exCount = 5;
    saveExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount);
    cout << "Default exams created & saved." << endl;
}

//load Time table
void loadTimetable(char**& ttcode, char**& ttcourse, char**& ttinstructor, char**& ttroom, int*& ttday, int*& ttStartTime, int*& ttEndTime, int& ttCount, int& ttCap, int Column_size)
{
    ifstream fin("timetable.txt");

    if (!fin.is_open())  //if file not open load the default timetable data 
    {
        cout << "unable to open the file — loading defaults...\n";
        loadDefaultTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, Column_size);
        return;
    }
    int count;
    fin >> count;
    fin.ignore(1000, '\n');

    if (count < 0) //if no data saved in file then load the default store timetable file
    {
        cout << "No record found — loading defaults.\n";
        fin.close();
        loadDefaultTimetable(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, Column_size);
        return;
    }

    if (count > ttCap) //if count capacity is more that tt arrays capacity grow it 
    {
        growTT(ttcode, ttcourse, ttinstructor, ttroom, ttday, ttStartTime, ttEndTime, ttCount, ttCap, count * 2, Column_size);
    }
    char* temp = new char[Column_size];
    for (int i = 0; i < count; i++)
    {
        fin.getline(temp, Column_size); //takes data in temp array
        safecopy(*(ttcode + i), temp, Column_size); //copy the taken data into original array 
        fin.getline(temp, Column_size);
        safecopy(*(ttcourse + i), temp, Column_size);
        fin.getline(temp, Column_size);
        safecopy(*(ttinstructor + i), temp, Column_size);
        fin.getline(temp, Column_size);
        safecopy(*(ttroom + i), temp, Column_size);
        fin >> *(ttday + i) >> *(ttStartTime + i) >> *(ttEndTime + i);
        fin.ignore(1000, '\n');
    }
    ttCount = count;
    fin.close();
    cout << "  Timetable loaded (" << ttCount << " entries)." << endl;

    delete[] temp;
    temp = nullptr;
}

//load exam schedule
void loadExams(char**& excode, char**& EXhall, int*& exdate, int*& exStartTime, int*& exEndTime, int& exCount, int& exCap, int Column_size)
{
    ifstream fin("exams.txt");
    if (!fin.is_open())
    {
        cout << "  unable to open the file — loading defaults..." << endl;
        loadDefaultExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, Column_size);
        return;
    }
    int count;
    fin >> count;
    fin.ignore(1000, '\n');

    if (count < 0)
    {
        cout << "NO record found — loading defaults.\n";
        fin.close();
        loadDefaultExams(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, Column_size);
        return;
    }
    if (count > exCap)
        growEX(excode, EXhall, exdate, exStartTime, exEndTime, exCount, exCap, count * 2, Column_size);

    char* temp = new char[Column_size];
    for (int i = 0; i < count; i++)
    {
        fin.getline(temp, Column_size);
        safecopy(*(excode + i), temp, Column_size);
        fin.getline(temp, Column_size);
        safecopy(*(EXhall + i), temp, Column_size);
        fin >> *(exdate + i) >> *(exStartTime + i) >> *(exEndTime + i);
        fin.ignore(1000, '\n');
    }
    exCount = count;
    fin.close();
    cout << "  Exams loaded (" << exCount << " entries).\n";

    delete[] temp;
    temp = nullptr;
}
//-----------------------------------------------------------------------------------------------------------------------------------//
                                      //~~~~~~~~~~`Thank you`~~~~~~~~~//