#include <cmath>
#include <QApplication>
#include <QTimer>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_point_data.h>

int main(int argc, char **argv)
{
  QApplication a(argc, argv);

  QwtPlot plot(QwtText("travis_qmake_gcc_cpp14_qt5_qwt"));
  plot.setGeometry(0,0,640,400);
  plot.setAxisScale(QwtPlot::xBottom, 0.0,2.0 * M_PI);
  plot.setAxisScale(QwtPlot::yLeft,-1.0,1.0);

  QwtPlotCurve curve("Sine");
  std::vector<double> xs;
  std::vector<double> ys;
  for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 100.0))
  {
    xs.push_back(x);
    ys.push_back(std::sin(x) * std::cos(x));
  }
  QwtPointArrayData * const data = new QwtPointArrayData(&xs[0],&ys[0],xs.size());
  curve.setData(data);
  curve.attach(&plot);

  plot.show();

  //In demo mode, close after 1 second
  if (argc == 2 && argv[1] == std::string("--demo"))
  {
    QTimer * const timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), &plot, SLOT(close()));
    timer->start(1000);
  }
  return a.exec();
}
