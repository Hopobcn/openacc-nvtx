/*
 *  Copyright 2015 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include <stdio.h>
#include <openacc.h>
// Prior to PGI 15.7 the profiling interface prototype was based on TR-14-2.
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
#include <pgi_acc_prof.h>
#else
#include <acc_prof.h>
#endif
#include <wchar.h>
#include <nvToolsExt.h>

#define bufsize 1024

void oaccNvtxName(acc_prof_info *profinfo, char* name, char* event)
{
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
  snprintf(name, bufsize, "%s (%s:%d)", 
           event, profinfo->funcname, profinfo->lineno);
#else
  snprintf(name, bufsize, "%s (%s:%d)", 
           event, profinfo->func_name, profinfo->line_no);
#endif
}

void oaccNvtxRegister(acc_prof_info *profinfo, 
                      acc_event_info *eventinfo, 
                      acc_api_info *apiinfo)
{
  char name[bufsize];
  nvtxEventAttributes_t eventAttrib = {0}; 

  eventAttrib.version   = NVTX_VERSION; 
  eventAttrib.size      = NVTX_EVENT_ATTRIB_STRUCT_SIZE; 
  eventAttrib.colorType = NVTX_COLOR_ARGB; 

#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
  switch(profinfo->eventtype) 
#else
  switch(profinfo->event_type) 
#endif
  {
#if defined(__PGIC__) && ((__PGIC__ <= 16) && (__PGIC_MINOR__ < 4))
    case acc_ev_init_start :
#else
    case acc_ev_device_init_start :
#endif
      oaccNvtxName(profinfo, name, "device init");
      eventAttrib.color = 0xffff00; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
    case acc_ev_device_shutdown_start :
      oaccNvtxName(profinfo, name, "device shutdown");
      eventAttrib.color = 0xffbf00; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
    case acc_ev_data_construct_enter_start :
#else
    case acc_ev_enter_data_start :
#endif
      oaccNvtxName(profinfo, name, "enter data");
      eventAttrib.color = 0xff8000; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
    case acc_ev_data_construct_exit_end :
#else
    case acc_ev_exit_data_start :
#endif
      oaccNvtxName(profinfo, name, "exit data");
      eventAttrib.color = 0xff4000; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
    case acc_ev_update_construct_start :
#else
    case acc_ev_update_start :
#endif
      oaccNvtxName(profinfo, name, "update");
      eventAttrib.color = 0xff0080; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
    case acc_ev_compute_construct_start :
      oaccNvtxName(profinfo, name, "kernels");
      eventAttrib.color = 0xbf00ff; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
    case acc_ev_enqueue_launch_start :
      oaccNvtxName(profinfo, name, "launch");
      eventAttrib.color = 0x8000ff; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
    case acc_ev_enqueue_upload_start :
      oaccNvtxName(profinfo, name, "upload");
      eventAttrib.color = 0xbfff00; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
    case acc_ev_enqueue_download_start :
      oaccNvtxName(profinfo, name, "download");
      eventAttrib.color = 0x80ff00; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
    case acc_ev_wait_start :
      oaccNvtxName(profinfo, name, "wait");
      eventAttrib.color = 0x0000ff; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
#if defined(__PGI__) && ((__PGI__ <= 15) && (__PGI_MINOR__ < 7))
    case acc_ev_implicit_wait_start :
      oaccNvtxName(profinfo, name, "implicit wait");
      eventAttrib.color = 0xffff00; 
      eventAttrib.messageType = NVTX_MESSAGE_TYPE_ASCII; 
      eventAttrib.message.ascii = name;
      nvtxRangePushEx(&eventAttrib);
      break;
#endif
#if defined(__PGIC__) && ((__PGIC__ <= 16) && (__PGIC_MINOR__ < 4))
    case acc_ev_init_end :
#else
    case acc_ev_device_init_end :
#endif
    case acc_ev_device_shutdown_end :
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
    case acc_ev_data_construct_enter_end :
#else
    case acc_ev_enter_data_end :
#endif
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
    case acc_ev_data_construct_exit_end :
#else
    case acc_ev_exit_data_end :
#endif
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
    case acc_ev_update_construct_end :
#else
    case acc_ev_update_end :
#endif
    case acc_ev_compute_construct_end :
    case acc_ev_enqueue_launch_end :
    case acc_ev_enqueue_upload_end :
    case acc_ev_enqueue_download_end :
    case acc_ev_wait_end :
#if defined(__PGI__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
    case acc_ev_implicit_wait_end :
#endif
      nvtxRangePop();
      break;
  }
}

typedef void (*regroutine)( acc_event_t, acc_prof_callback_t, int );
#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
void acc_register_library(regroutine regFunc, regroutine unregFunc)
#else
void acc_register_library(acc_prof_reg regFunc, acc_prof_reg unregFunc, acc_prof_lookup lookup)
#endif
{
  fprintf(stderr, "REGISTERING NVTX LIBRARY\n");
  regFunc(acc_ev_device_init_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_device_init_end, oaccNvtxRegister, 0);

  regFunc(acc_ev_device_shutdown_end, oaccNvtxRegister, 0);
  regFunc(acc_ev_device_shutdown_end, oaccNvtxRegister, 0);

  regFunc(acc_ev_device_init_end, oaccNvtxRegister, 0);
  regFunc(acc_ev_device_init_end, oaccNvtxRegister, 0);

#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
  regFunc(acc_ev_data_construct_enter_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_data_construct_enter_end, oaccNvtxRegister, 0);
#else 
  regFunc(acc_ev_enter_data_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_enter_data_end, oaccNvtxRegister, 0);
#endif

#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
  regFunc(acc_ev_data_construct_exit_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_data_construct_exit_end, oaccNvtxRegister, 0);
#else  
  regFunc(acc_ev_exit_data_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_exit_data_end, oaccNvtxRegister, 0);
#endif

#if defined(__PGIC__) && ((__PGIC__ <= 15) && (__PGIC_MINOR__ < 7))
  regFunc(acc_ev_update_construct_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_update_construct_end, oaccNvtxRegister, 0);
#else
  regFunc(acc_ev_update_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_update_end, oaccNvtxRegister, 0);
#endif

  regFunc(acc_ev_compute_construct_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_compute_construct_end, oaccNvtxRegister, 0);
 
  regFunc(acc_ev_enqueue_launch_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_enqueue_launch_end, oaccNvtxRegister, 0);
  
  regFunc(acc_ev_enqueue_upload_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_enqueue_upload_end, oaccNvtxRegister, 0);
  
  regFunc(acc_ev_enqueue_download_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_enqueue_download_end, oaccNvtxRegister, 0);
 
  regFunc(acc_ev_wait_start, oaccNvtxRegister, 0);
  regFunc(acc_ev_wait_end, oaccNvtxRegister, 0);
}

#if 0
void __acc_prof_register
	( acc_prof_register_t acc_register, acc_prof_register_t acc_unregister )
{
  acc_register_library(acc_register, acc_unregister);
}
#endif
