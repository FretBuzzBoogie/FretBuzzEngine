#pragma once
#include "utils/resource_container.h"
#include "shader.h"

namespace FRETBUZZ
{
	class  ShaderManager : public ResourceContainer<std::map<Shader::SHADER_TYPE, Shader*>>
	{
	public:
		static ShaderManager* initialize();
		static ShaderManager* get();
		void destroy();
		static Shader* getShaderOfType(Shader::SHADER_TYPE a_ShaderType);

		void registerShader(Shader::SHADER_TYPE a_ShaderType, Shader* a_pShader);
		void unregisterShader(Shader::SHADER_TYPE a_ShaderType);


	private:
		static ShaderManager* s_pInstance;

		ShaderManager();
		~ShaderManager();
		void unregisterAll();
	};
}