project : 
I am involved in a project to port FreeRTOS to STM32 for drone,
and I need to add the existing firmware to the RTOS tasks. The existing firmware without RTOS.

challenge:
The challenge for me is that this is the first time to port RTOS to an existing firmware,
because I have previously developed based on existing firmware or developed from 0 to 1. 

plan:
1. So my plan is to review the code first.
2. understand the code structure and functions, and understand independent functions of code project.
3. Then port the RTOS, create tasks.
4. break down the code project base on independent functions and add to the RTOS tasks
5. continue test and modify and optimize
6. finally the original firmware running well under the FreeRTOS.

learn:
At the beginning of the project, a comprehensive code design should be done, 
1.such as whether based on RTOS
2.what is the independent functions
3.Design code framework, function framework, data structure
so that can make maintenance and continuous development easier.

Suggestion:
1.The design and planning of the project are very important, and the code architecture design also very important. 
2.These should be written into documents, and then execute the plan according to documents.
3.And Using git to manage the code.
so, these can reduce a lot of wasted time and improve code maintenance and improve code continuous development.
