/**
 *       Copyright 2012-2015 The MathWorks, Inc.
 */

/**
 * Polyspace Bug finder example.
 * This example shows defects caused by resource management errors.
 *
 * This example will show you how selected defects will be handled by the
 * Polyspace Bug Finder.
 * Each defect is depicted in a specific function, and a sibling function
 * showing the fixed code is then shown.
 */

#include <stdio.h>


/*============================================================================
 *  USING ALREADY CLOSED RESOURCE
 *==========================================================================*/
const char* logfile = "my_file.log";
void bug_closedresourceuse_fprintf(void) {
  FILE* fp = fopen(logfile, "w");
  (void)fclose(fp);
  (void)fprintf(fp, "I am writing");   /* Defect: Writing in a closed file */
}

void corrected_closedresourceuse_fprintf(void) {
  FILE* fp = fopen(logfile, "w");
  (void)fprintf(fp, "I am writing");   /* Fix: Write then close the file */
  (void)fclose(fp);
}


/*============================================================================
 *  DOUBLE OPENED RESOURCE
 *==========================================================================*/
void bug_doubleresourceopen(void) {
  FILE* fpa = fopen(logfile, "w");
  if (fpa == NULL) {
      return;
  }
  (void)fprintf(fpa, "I am writing");
  FILE* fpb = fopen(logfile, "r");      /* Defect: Opening the file twice */
  (void)fclose(fpa);
  (void)fclose(fpb);
}

void corrected_doubleresourceopen(void) {
  FILE* fpa = fopen(logfile, "w");
  if (fpa == NULL) {
      return;
  }
  (void)fprintf(fpa, "I am writing");
  (void)fclose(fpa);                          /* Fix: Close before reopening the same file */
  FILE* fpb = fopen(logfile, "r");
  (void)fclose(fpb);
}


/*============================================================================
 *  DOUBLE CLOSED RESOURCE
 *==========================================================================*/
void bug_doubleresourceclose(int i) {
  FILE* fp = fopen(logfile, "w");
  if (i>0) {
      (void)fprintf(fp, "I am writing");
      (void)fclose(fp);
  }
  (void)fclose(fp);                    /* Defect: Closing the file twice */
}

void corrected_doubleresourceclose(int i) {
  FILE* fp = fopen(logfile, "w");
  if (i>0) {
      (void)fprintf(fp, "I am writing");
  }
  (void)fclose(fp);                    /* Fix: Only one close call */
}


/*============================================================================
 *  WRITING TO A READ-ONLY RESOURCE
 *==========================================================================*/
void bug_readonlyresourcewrite(void) {
    FILE* fp = fopen(logfile, "r");
    (void)fprintf(fp, "I am writing");         /* Defect: Writing to a file opened as "r" */
    (void)fclose(fp);
}

void corrected_readonlyresourcewrite(void) {
    FILE* fp = fopen(logfile, "w");
    (void)fprintf(fp, "I am writing");         /* Fix: Writing to a file opened as "w" */
    (void)fclose(fp);
}


/*============================================================================
 *  RESOURCE LEAK
 *==========================================================================*/
const char* logfile2 = "my_file2.log";
void bug_resourceleak(void) {
    FILE* fp = fopen(logfile, "w");
    (void)fprintf(fp, "I am writing");
    fp = fopen(logfile2, "w");         /* Defect: File has not been closed */
    (void)fprintf(fp, "I am writing to log2 too");
    (void)fclose(fp);
}

void corrected_resourceleak(void) {
    FILE* fp = fopen(logfile, "w");
    (void)fprintf(fp, "I am writing");
    (void)fclose(fp);         /* Fix: Closing the file */
    fp = fopen(logfile2, "w");
    (void)fprintf(fp, "I am writing to log2 too");
    (void)fclose(fp);
}

