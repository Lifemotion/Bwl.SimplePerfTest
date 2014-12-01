Module SimplePerfTest

    Sub Main()
        Console.WriteLine("Bwl.SimplePerfTest")
        Console.WriteLine("Preparing...")
        Dim rnd As New Random
        Dim repeats = 10
        Dim float_limit = 10.0
        Dim float_limit_sub = 9.0
        Dim int_limit = 10000
        Dim int_limit_sub = 9000
        Dim floats(1024 * 1024) As Single
        Dim ints(1024 * 1024) As Integer

        For i = 0 To floats.Length - 1
            floats(i) = rnd.NextDouble * float_limit + 1.0
        Next
        For i = 0 To ints.Length - 1
            ints(i) = rnd.Next(1000, 9000)
        Next
        Console.WriteLine("Multiplying " + floats.Length.ToString + " floats " + ints.Length.ToString + " ints")
        Dim start As DateTime = Now


        For i = 1 To repeats
            For j = 0 To floats.Length - 2
                floats(j + 1) = floats(j + 1) * floats(j)
                While floats(j + 1) > float_limit
                    floats(j + 1) -= float_limit_sub
                End While
            Next
        Next
        Console.WriteLine("Floats result (ms): " + ((Now - start).TotalMilliseconds / repeats).ToString)

        start = Now
        Dim mask = 1023
        For i = 1 To repeats
            For j = 0 To ints.Length - 2
                ints(j + 1) = (ints(j + 1) * ints(j)) Mod mask + 97
                ' While ints(j + 1) > int_limit
                'ints(j + 1) -= int_limit_sub
                ' End While
            Next
        Next
        Console.WriteLine("Ints result (ms): " + ((Now - start).TotalMilliseconds / repeats).ToString)

        Console.ReadLine()
    End Sub

End Module
