//
//  Layer.h
//  Hazel
//
//  Created by wufanfan on 2022/4/30.
//

#ifndef Layer_h
#define Layer_h

#include "Core.h"
#include "Events/Event.h"

namespace Hazel {

class Layer
{
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();
    
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate() {}
    virtual void OnEvent(Event& event) {}
    
    inline const std::string& GetName() const { return m_DebugName; }
protected:
    std::string m_DebugName;
};

}

#endif /* Layer_h */
