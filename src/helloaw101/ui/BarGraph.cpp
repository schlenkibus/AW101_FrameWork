#include "BarGraph.h"
#include "../../libaw101/AW101Layout.h"
#include "../TestModel.h"

class DrawBarGraphJavaScript : public JavaScript {
public:
    DrawBarGraphJavaScript(const std::string& id, TestModel* model) {
        m_id = id;
        m_model = model;
    }
    std::string m_id;
    TestModel* m_model;
    const std::string getScriptContent() const override {
        return
        "var canvas = document.getElementById('" + m_id + "');"\
        "var ctx = canvas.getContext('2d');"\
        "ctx.clearRect(0, 0, canvas.width, canvas.height);" +
                [this]{
                    std::string ret;
                    const auto step = m_model->m_synth.m_data.m_samples.m_data.size() / 10.f;
                    int i = 0;
                    ret += "ctx.beginPath();";
                    ret += "ctx.moveTo(0, 50);";
                    for(auto& bar: m_model->m_synth.m_data.m_samples.m_data) {
                        ret += "ctx.lineTo(" + std::to_string(i++) + ", " + std::to_string(50 + 50 * bar) + ");";
                    }
                    ret += "ctx.stroke();";
                    return ret;
                }() +
                "";
    }
};

BarGraph::BarGraph(AW101Layout *parent, TestModel *model) : Control(parent) {
    m_model = model;
    m_parent->getCallbackManager()->eval(DrawBarGraphJavaScript(m_id.id, m_model).getScriptContent());
}

void BarGraph::computeNode() {
    clear();
    m_node.SetName("canvas.Canvas#"+m_id.id);
    m_node.SetAttribute("heigth", "100px");
    m_node.SetAttribute("width", "250px");
}

void BarGraph::redraw() {
    m_parent->getCallbackManager()->eval(DrawBarGraphJavaScript(m_id.id, m_model).getScriptContent());
}
