#include "step.h"
#include "parse.h"


#define BUFFER_LENGTH 1024000

void step::DeserializeFile(const char * path, const ReadCallbackFunc & cb)
{
	auto fd = fopen(path, "rb");
	
	pcre2_code *re;
	PCRE2_SPTR pattern = (PCRE2_SPTR)"95=(\\d+)\\x01";     /* PCRE2_SPTR is a pointer to unsigned code units of */
	int errornumber;

	PCRE2_SIZE erroroffset;


	re = pcre2_compile(
		pattern,               /* the pattern */
		PCRE2_ZERO_TERMINATED, /* indicates pattern is zero-terminated */
		0,                     /* default options */
		&errornumber,          /* for error number */
		&erroroffset,          /* for error offset */
		NULL);                 /* use default compile context */

							   /* Compilation failed: print the error message and exit. */

	if (re == NULL)
	{
		PCRE2_UCHAR buffer[256];
		pcre2_get_error_message(errornumber, buffer, sizeof(buffer));
		printf("PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset, buffer);
		exit(-1);
	}

	char buffer[BUFFER_LENGTH];

	int r = 0, offset = 0, index = 0;
	while (!feof(fd)) {
		r = fread(buffer + offset, sizeof(char), BUFFER_LENGTH - offset, fd);

		while (true) {
			pcre2_match_data *match_data;
			match_data = pcre2_match_data_create_8(1024, NULL);

			int rc;
			rc = pcre2_match(
				re,                   /* the compiled pattern */
				(PCRE2_SPTR)buffer,   /* the subject string */
				BUFFER_LENGTH,        /* the length of the subject */
				index,                /* start at index in the subject */
				0,                    /* default options */
				match_data,           /* block for storing the result */
				NULL);                /* use default match context */

			if (rc < 0)
			{
				switch (rc) {
				case PCRE2_ERROR_NOMATCH: 
					printf("No match\n"); 
					break;

				default: printf("Matching error %d\n", rc); break;
				}
				pcre2_match_data_free(match_data);   /* Release memory used for the match */
				pcre2_code_free(re);                 /* data and the compiled pattern. */
			}

			PCRE2_SIZE *ovector;
			ovector = pcre2_get_ovector_pointer(match_data);

			int msg_size = ParseInt(buffer + ovector[2]);
			if (ovector[1] + msg_size + 4 > BUFFER_LENGTH)
			{
				assert(ovector[1] > BUFFER_LENGTH / 2);
				memcpy(buffer, buffer + ovector[0], BUFFER_LENGTH - ovector[0]);
				offset = BUFFER_LENGTH - ovector[0];
				index = 0;
				break;
			}

			char* msg_buffer = new char[msg_size];
			memcpy(msg_buffer, buffer + ovector[1] + 3, msg_size);
			cb(msg_buffer, msg_size);
			index = ovector[1] + 3 + msg_size + 1;

			delete[] msg_buffer;
			pcre2_match_data_free(match_data);
			
		}
	}
}
