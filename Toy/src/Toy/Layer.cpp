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
}