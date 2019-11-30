//
//  main.c
//  quiz2_19
//
//  Created by 王英鉴 on 2019/9/30.
//  Copyright © 2019 王英鉴. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
void main (){
        for (int i=0; i<3; i++)
                fork();
                printf (&quot;PID: %d n&quot; getpid());
            wait ()
        }
}
