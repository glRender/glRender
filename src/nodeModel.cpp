#include "nodeModel.hpp"

namespace glRender
{

NodeModel::NodeModel(Model * model) :
	m_model(model)
{

}

NodeModel::~NodeModel()
{

}

void NodeModel::update()
{

}

void NodeModel::draw(Camera * camera)
{
	m_model->draw(camera);
}

Model * NodeModel::model()
{
	return m_model;
}

}