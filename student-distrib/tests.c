#include "tests.h"
#include "x86_desc.h"
#include "lib.h"

#define PASS 1
#define FAIL 0

/* format these macros as you see fit */
#define TEST_HEADER 	\
	printf("[TEST %s] Running %s at %s:%d\n", __FUNCTION__, __FUNCTION__, __FILE__, __LINE__)
#define TEST_OUTPUT(name, result)	\
	printf("[TEST %s] Result = %s\n", name, (result) ? "PASS" : "FAIL");

#define TEST_MAX_FILE_SIZE 
#define TEST_MAX_FILENAME_SIZE

static inline void assertion_failure(){
	/* Use exception #15 for assertions, otherwise
	   reserved by Intel */
	asm volatile("int $15");
}



/* Checkpoint 1 tests */

/* IDT Test - Example
 * 
 * Asserts that first 10 IDT entries are not NULL
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Load IDT, IDT definition
 * Files: x86_desc.h/S
 */
int idt_test(){
	TEST_HEADER;

	int i;
	int result = PASS;
	for (i = 0; i < 10; ++i){
		if ((idt[i].offset_15_00 == NULL) && 
			(idt[i].offset_31_16 == NULL)){
			assertion_failure();
			result = FAIL;
		}
	}

	return result;
}

/* IDT User Test 1
 * 
 * Forcing a divide-by-zero interrupt
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Load IDT, IDT definition
 * Files: x86_desc.h/S
 */
int idt_test_USER_1(){
	TEST_HEADER;

	int i;
	int result = PASS;
	i = 10;
	i = i/0;
	
	return result;
}

/* RTC User Test 1
 * 
 * Trigger the OS clock at a set frequency
 * Inputs: None
 * Outputs: Flashing screen
 * Side Effects: Flashing screen
 * Coverage: Load RTC, RTC definition
 * Files: x86_desc.h/S
 */
int rtc_test_USER_1(){
	TEST_HEADER;
	// asm();
	while(1){
		test_interrupts();
	}
}

/* Paging User Test 1
 * 
 * Check pointer null
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Paging correct functionality
 * Files: x86_desc.h/S
 */
int page_test_USER_1(){
	TEST_HEADER;
	char x;
	x = *(char*)NULL;
	return FAIL;
}

/* Paging User Test 1
 * 
 * Check specific addresses
 * Inputs: None
 * Outputs: PASS/FAIL
 * Side Effects: None
 * Coverage: Paging address edge cases
 * Files: x86_desc.h/S
 */
int page_test_USER_2(){
	TEST_HEADER;
	char x;
	x = *(char*)0xB8000;
	x = *(char*)0xB9000-1;
	x = *(char*)0x400000;
	x = *(char*)0x800000-1;
	return PASS;
}


// add more tests here

/* Checkpoint 2 tests */

/*

*/
int32_t small_files_read_test_USER_1(){
	TEST_HEADER;

	int32_t fd;
	fd = open_file((uint8_t*)"frame0.txt");

	uint8_t buffer [MAX_FILE_SIZE];

	if(fd < 0){
		puts("Fail");
		return;
	}

	int32_t bytes_read = file_read(fd, buffer, MAX_FILE_SIZE);
	if(bytes_read < 0){
		puts("Fail");
		return;
	}

	file_close(fd);
	return bytes_read;
}

/*
ls, read files

terminal
type
copy over buffer

*/
int terminal_test_USER_1(){
	TEST_HEADER;
	int nbytes;
	char buf[1024];
	while(1){
		terminal_write(0, (uint8_t*)"size 10 \n", 16); //buffer < 128
		nbytes = terminal_read(0, buf, 10);
		terminal_write(0, buf, nbytes);

		terminal_write(0, (uint8_t*)"size 128 \n", 17); //max buffer size
		nbytes = terminal_read(0, buf, 128);
		terminal_write(0, buf, nbytes);

		terminal_write(0, (uint8_t*)"size 129 \n", 17); //
		nbytes = terminal_read(0, buf, 150);
		terminal_write(0, buf, nbytes);
	}
}



/*
Discord Test #1: alter RTC frequency to chagne frequency of spam-typed keyboard characters
Test: filesystem_print_contents_test_USER
Inputs: None
Outputs: printed list of all file names
Coverage: read/write, RTC frequency change
*/
void rtc_test_USER() {
    TEST_HEADER;

    uint32_t rtc_frequency;
    char frequency_input[BUF_SIZE];
    int write_result;

    terminal_open(0);

    while (1) {
		rtc_frequency = 0;
        printf("Enter desired clock frequency: ");
        int num_digits = terminal_read(0, 0, frequency_input, 10);
        
        for (int i = 0; i < num_digits; ++i) {
            rtc_frequency = rtc_frequency * 10 + (uint32_t)(frequency_input[i] - '0');
        }

        RTC_open(0);
        write_result = RTC_write(0, &rtc_frequency, 4);

		int iteration_count = 0;
		while (iteration_count < MAX_ITERATIONS) {
			RTC_read(0, 0, &rtc_frequency, 4);
			putc('1');
			iteration_count++;
        RTC_close(0);
    }

    terminal_close(0);
}





/*
Discord Test #2: print out  list of all the file names
Test: filesystem_print_contents_test_USER
Inputs: None
Outputs: printed list of all file names
Coverage: Terminal driver, read/write
*/

void filesystem_name_list_test_USER() {
    TEST_HEADER;

    char current_filename[TEST_MAX_FILENAME_SIZE + 1];
    char directory_listing[MAX_TOTAL_FILE_NAME];

    int result = dir_open((uint8_t*)".");
	
    read_dir(0, 0, directory_listing, MAX_TOTAL_FILE_NAME);
    close_dir();

    int current_read_position = 0;
    int last_filename_position = 0;
    dentry_t current_directory_entry;
    char temporary_buffer[TEST_MAX_FILE_SIZE];

    while (directory_listing[current_read_position] != '\0') {
        current_filename[current_read_position - last_filename_position] = directory_listing[current_read_position];

        if (directory_listing[current_read_position] == '\n') {
            current_filename[current_read_position - last_filename_position] = '\0';
            last_filename_position = current_read_position + 1;

            read_dentry_by_name((uint8_t*)current_filename, &current_directory_entry);
            temporary_buffer[TEST_MAX_FILE_SIZE - 1] = '\0';

            rtc_open((uint8_t*)current_filename);
            rtc_read(0, 0, NULL, TEST_MAX_FILE_SIZE);
            rtc_close(0);

            printf("Name: %s Type: %d Inode number: %d\n",
                current_directory_entry.filename, current_directory_entry.file_type,
                current_directory_entry.inode_idx);
        }

        if (directory_listing[current_read_position] != '\n' && directory_listing[current_read_position] != '\0') {
            current_read_position++;
            continue;
        }

        current_read_position++;
    }

    current_filename[current_read_position - last_filename_position] = '\0';
    last_filename_position = current_read_position + 1;

    read_dentry_by_name((uint8_t*)current_filename, &current_directory_entry);
    temporary_buffer[MAX_FILE_SIZE_INTEST - 1] = '\0';

    rtc_open((uint8_t*)current_filename);
    rtc_read(0, 0, NULL, MAX_FILE_SIZE_INTEST);
	
    rtc_close(0);

    printf("file_type: %d filename: %s inode num: %d\n",
        current_directory_entry.file_type, current_directory_entry.filename,
        current_directory_entry.inode_idx);

    test_end();
}




/*
*/

/* 
Discord Test #3: print out file contents to terminal
Test: filesystem_print_contents_test_USER
Inputs: None
Outputs: print file's full content onto the terminal based on index in  boot_block
Coverage: File system open, close, read, write
 */

void filesystem_print_contents_test_USER() {
	
    dentry_t dentry;

    for (int i = 0; i < boot_block.num_dentries; i++) {

        RTC_open(NULL);
        RTC_read(0, NULL, 0, MAX_FILE_SIZE_INTEST);
        RTC_close(0);

        printf("total index: %d \n", boot_block.num_dentries);
        printf("current index: %d\n", i);

        read_dentry_by_index(i, &dentry);
        print_types(dentry);
        print_dentry(dentry);
    }

    test_end();
}




/* Checkpoint 3 tests */
/* Checkpoint 4 tests */
/* Checkpoint 5 tests */


/* Test suite entry point */
void launch_tests(){
	// TEST_OUTPUT("idt_test", idt_test_USER_1());
	// TEST_OUTPUT("idt_test", idt_test());
	// TEST_OUTPUT("idt_test", syscall_handler_test());
	// TEST_OUTPUT("rtc_test", rtc_test_USER_1());
	// TEST_OUTPUT("page_test", page_test_USER_1());
	TEST_OUTPUT("page_test", page_test_USER_2());
	// launch your tests here
}
