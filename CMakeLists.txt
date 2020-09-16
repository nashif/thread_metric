cmake_minimum_required(VERSION 3.8.2)

include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)
project(NONE)


target_sources(app PRIVATE tm_preemptive_scheduling_test.c)
#target_sources(app PRIVATE tm_cooperative_scheduling_test.c)
#target_sources(app PRIVATE tm_synchronization_processing_test.c)
#target_sources(app PRIVATE tm_interrupt_processing_test.c)
#target_sources(app PRIVATE tm_interrupt_preemption_processing_test.c)
target_sources(app PRIVATE tm_porting_layer_zephyr.c)
target_compile_definitions(app PRIVATE ENABLE_PRINTF=1)
