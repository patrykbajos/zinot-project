//
// Created by patryk on 11.01.17.
//
#include <gtest/gtest.h>

#include <zinot-utils/json/JsonReader.hpp>
#include <zinot-engine/dao/ShaderDescDao.hpp>

class ShaderDescDaoTest : public ::testing::Test
{
protected:
   Zinot::ShaderDescDao descDao;
};

TEST_F(ShaderDescDaoTest, BasicTest)
{
   EXPECT_TRUE(Zinot::JsonReader::loadFromJsonFile("media/shaders/pbrDoubleUVShader.shd", descDao));

   EXPECT_TRUE(descDao.getShdAttributes()["vertUv2"] == Zinot::ShaderDescDao::AttribType::UV);

   const Zinot::ShaderDescDao::UniformType & texAoUni = descDao.getShdUniforms()["texAO"];
   EXPECT_TRUE(texAoUni.dataType == Zinot::ShaderDescDao::UniformDataType::Sampler2D);
   EXPECT_TRUE(texAoUni.defVal.sampler2DDefaults == Zinot::ShaderDescDao::UniformDefaults::Sampler2DDefaults::White);

   EXPECT_TRUE(descDao.getVsPath() == "media/shaders/pbrDoubleUVVert.glsl");
   EXPECT_TRUE(descDao.getFsPath() == "media/shaders/pbrDoubleUVFrag.glsl");
}
