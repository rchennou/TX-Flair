// %flair:license{
// This file is part of the Flair framework distributed under the
// CECILL-C License, Version 1.0.
// %flair:license}
//  created:    2013/04/21
//  filename:   config.h
//
//  author:     Guillaume Sanahuja
//              Copyright Heudiasyc UMR UTC/CNRS 7253
//
//  version:    $Id: $
//
//  purpose:    configuration du framework
//
//
/*********************************************************************/

#ifndef CONFIG_H
#define CONFIG_H

// stack size of nrt threads, comment it to use default value
#define NRT_STACK_SIZE 1024 * 1024 * 1

// stack size of rt threads, comment it to use default value
#define RT_STACK_SIZE 1024 * 100

// rt pipe size, comment it to use system heap
#define RT_PIPE_SIZE 1024 * 1024

// nrt pipe size
#define NRT_PIPE_SIZE 1024 * 100

// rt log heap size
#define LOG_HEAP 1024 * 100

// xml heap size
#define XML_HEAP 5 * 1024 * 1024

// nrt pipe path
#define NRT_PIPE_PATH "/proc/xenomai/registry/native/pipes/"

// min priority for Threads
#define MIN_THREAD_PRIORITY 20

// max priority for Threads
#define MAX_THREAD_PRIORITY 99

// priority of the FrameworkManager task (manages udt connection)
#define FRAMEWORK_TASK_PRIORITY 1

// timeout in ms for select
#define SELECT_TIMEOUT_MS 200

// type of xml root element
#define XML_ROOT_TYPE "root"

// name of xml root element
//#define XML_ROOT_ELEMENT "Manager"

// name of main tabwidget
#define XML_MAIN_TABWIDGET "Main_TabWidget"

// name of app tabwidget
#define XML_APP_TABWIDGET "App_TabWidget"

// use compression for messages with ground station
#define COMPRESS_FRAMES

// size of buffer shunck
#define COMPRESS_CHUNK 1024

#endif // CONFIG_H
