#pragma once

namespace Toy {

	class RendererContext
	{
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};

}