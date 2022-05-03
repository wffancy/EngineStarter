//
//  LayerStack.h
//  Hazel
//
//  Created by wufanfan on 2022/4/30.
//

#ifndef LayerStack_h
#define LayerStack_h

#include "Core.h"
#include "Layer.h"

namespace Hazel {

class LayerStack
{
public:
    LayerStack();
    ~ LayerStack();
    
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* overlay);
    
    std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
    std::vector<Layer*>::iterator end() { return m_Layers.end(); }
private:
    std::vector<Layer*> m_Layers;
    std::vector<Layer*>::iterator m_LayerInsert;
};

}

#endif /* LayerStack_h */
