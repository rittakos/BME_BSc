
String EvaluateSalaryAndReturnName(Employee e)
{
    //A feltetel vagy teljesul vagy nem
    if (e.Title() == "CEO" || e.Salary() > 100000) //A rovidzar tulajdonsag es operatokhivasok
    {                                              //valamint e nem letezik lehet elagazas
        cout << e.First() << " " << e.Last() //A First es Last fuggvenyek es operatorok
            << " is overpaid" << endl;       //valamint IO muveletek okozhatnak mas lefutast
    }
    return e.First() + " " + e.Last();//A + operatorok megirasa lehet hibas, e nem biztos, hogy letezik
                                      //A String konstruktorhivas is dobhat kivetelt. 5 lefutas
}


/*
String EvaluateSalaryAndReturnName(Employee e) 
{
    if (e.Title() == "CEO" || e.Salary() > 100000) 
    {
        cout << e.First() << " " << e.Last()
            << " is overpaid" << endl;
    }
    return e.First() + " " + e.Last();
}

teljesul az if:
{
    Nem letezik e
    {
        #
    }
    Letezik e
    {
        A || rovidzartulajdonsaga miatt nem foglalkozik az e.Salaryval, ha e.Title feltetele igaz
        {
            A e.Title megirt == operatora rossz
            {
                #
            }Jo az operator
            {
                *A kiiro operatorok nem mukodnek
                {
                    #
                }mukodnek
                {
                    Visszatereshez tartozo 4 eset
                }
            }
        }
        Ha foglalkozik vele
        {
            valamelyik operator rossz
            {
                #
            }Jo az operator
            {
                Ugyanaz mint a * eset
                5 eset
            }
        }
    }
}
nem teljesul:
{
    Ha nem letezik e
    {
        #
    }
    letezik
    {
        A e.First es e.Last visszateresi erteke beepitett tipus
        {
            #
        }nem beepitett
        {
            Jol mukodnek az operatorok es nem dobnak kivetelt
            {
                A visszatereskor sikertelen a String konstruktorhivasa
                {
                    #
                }sikeres
                {
                    #
                }
            }kivetelt dobnak
            {
                #
            }
        }
    }
    5
}

lefutasi utak szama: 18 
*/