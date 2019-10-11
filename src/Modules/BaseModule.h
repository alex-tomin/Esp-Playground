#ifndef BASE_MODULE /* guard */
#define BASE_MODULE

class BaseModule {
      
   public:
      virtual void setup() = 0;
      virtual void loop() = 0;
};

#endif