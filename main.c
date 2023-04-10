#include

#include

#define MAXPROGRAMSIZE 100

#define MAXMEMORYSIZE 10

struct instruct

{

int opCode, deviceOrAddress;

};

struct instruct programMemory[MAXPROGRAMSIZE];

struct instruct instructionRegister;

int accumulate;

int memory[MAXMEMORYSIZE];

int progCount = 10;

int memoryAddRegis;

int memoryDataRegis;

int decod = 0;

void fetch_execute(void);

void load(void);

void store(void);

void add(void);

void sub(void);

void output(void);

void input(void);

void skipz(void);

void jump(void);

int main(int argc, char *argv[])

{

  

int c;

//read input file file.txt

FILE *file;

if(argc!=2)

{

printf("Please input the file!\n");

exit(1);

}

file = fopen(argv[1], "r");

  

if (file)

{

printf("Assembling the Program\n");

int programIndex = 0;

while ((c = getc(file)) != EOF)

{

c-='0';

if(c<0||c>9)

{

continue;

}

if(programIndex%2==0)

{

programMemory[progCount+programIndex/2].opCode=c;

}else

{

programMemory[progCount+programIndex/2].deviceOrAddress=c;

}

programIndex++;

}

printf("Program Assembled\n Run.\n");

/*for(i=progCount;i < progCount+3;i++){

   printf("\n%d %d",programMemory[i].opCode,programMemory[i].deviceOrAddress);

   }*/

while(decod!=7)

{

switch(decod)

{

case 0:

fetch_execute();

break;

case 1:

load();

break;

case 2:

add();

break;

case 3:

store();

break;

case 4:

sub();

break;

case 5:

input();

break;

case 6:

output();

break;

case 8:

jump();

break;

case 9:

skipz();

break;

}

}

printf("Program Complete\n");

fclose(file);

}else

{

printf("File not found\n");

}

system("PAUSE");

return 0;

}

void fetch_execute()

{

memoryAddRegis=progCount;

++progCount;

memoryDataRegis = programMemory[memoryAddRegis].deviceOrAddress;

instructionRegister.deviceOrAddress=memoryDataRegis;

memoryDataRegis = programMemory[memoryAddRegis].opCode;

instructionRegister.opCode=memoryDataRegis;

decod = instructionRegister.opCode;

}

//Loads the contents of instructionRegister address into A (A stand for Accumulator).

void load()

{

memoryAddRegis = instructionRegister.deviceOrAddress;

memoryDataRegis = memory[memoryAddRegis];

accumulate = memoryDataRegis;

decod = 0;

}

//Store the contents of A into instructionResister address

void store()

{

memoryAddRegis = instructionRegister.deviceOrAddress;

memoryDataRegis = accumulate;

memory[memoryAddRegis] = memoryDataRegis;

decod = 0;

}

//The data value stored at instructionRegister address is added to the A and the result is stored back in the A.

void add()

{

memoryAddRegis = instructionRegister.deviceOrAddress;

memoryDataRegis = memory[memoryAddRegis];

accumulate = accumulate+memoryDataRegis;

decod = 0;

}

//Subtracts the value located at instructionRegister address from the A and stored the result back in the A.

void sub()

{

memoryAddRegis = instructionRegister.deviceOrAddress;

memoryDataRegis = memory[memoryAddRegis];

accumulate = accumulate-memoryDataRegis;

decod = 0;

}

//Print out the contents of the AC in the output device.

void output()

{

int i = 0;

printf("PC = %d \t A = %d \t MEM = [",progCount,accumulate);

for(i=0;i

{

printf("%d, ",memory[i]);

}

printf("%d]\n",memory[i]);

decod = 0;

}

//A value from the input device is transferred into the A.

void input()

{

printf("Enter a number: ");

scanf("%d",&accumulate);

decod = 0;

}

//If the contents of the Accumulator = 0 the next instruction is skipped.

void skipz()

{

