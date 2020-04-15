There two function, 
function 1: fix the bug of judging connected fractures when Fracman is doing meshing
function 2: 


How to use:

function 1:
pre-processing (in Fracman):
	1. create a hybrid simulation that outer region is EPM and inner region is DFN
	2. create a DFN simulation in inner region
	3. "NOTICE": you had better set the same boundary conditions in both file *1
	3. export files and create mesh of both simulation
	4. export inner region file as region.sab

edMff:
	1. do what you should do
	2. 

post-processing (in Fracman):
	1. simulate hybrid simulation


function 2:


*1:  Which means that both file should contain the same conditions.
For example, if hybrid simulation used condition A, B, C then dfn simulation should use condition A, B, C also.
Where they were used at is not important.