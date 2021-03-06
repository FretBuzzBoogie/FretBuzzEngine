#pragma once

namespace FRETBUZZ
{
	class  IManagedResource
	{
	public:

		IManagedResource(bool a_bIsErrorWhileLoading = false)
			: m_bIsErrorWhileLoading{a_bIsErrorWhileLoading}
		{};

		virtual ~IManagedResource()
		{
			
		}

		bool getIsErrorWhileLoading() const
		{
			return m_bIsErrorWhileLoading;
		}

	protected:
		friend class ResourceManager;

		bool m_bIsErrorWhileLoading = false;

		///unloads the resource in managed child
		virtual void destroyResource() = 0;

	};
}