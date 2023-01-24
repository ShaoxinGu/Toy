#include "toypch.h"
#include "Layer.h"

namespace Toy{
    Layer::Layer(const std::string& debugName)
        : m_DebugName(debugName)
    {
    }

    Layer::~Layer()
    {
    }
    void Layer::OnAttach()
    {
    }
    void Layer::OnDetach()
    {
    }
    void Layer::OnUpdate()
    {
    }
}