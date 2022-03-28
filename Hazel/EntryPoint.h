//
//  EntryPoint.h
//  Hazel
//
//  Created by wufanfan on 2022/3/28.
//

#ifndef EntryPoint_h
#define EntryPoint_h

#ifdef HZ_PLATFORM_MAC

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
    printf("Hezel Engine");
    auto app = Hazel::CreateApplication();
    app->Run();
    delete app;
}


#endif


#endif /* EntryPoint_h */
