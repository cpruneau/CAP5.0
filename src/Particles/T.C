
void T()
{
  double v = 0;
  for (int k=2; k< 100000; k++)
    {
    v += std::log(double(k));
    cout << k << "   " << setw(20) << setprecision(14) << v << endl;
    }
}

