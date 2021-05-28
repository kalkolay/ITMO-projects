//
//  ContentView.swift
//  Modelling1
//
//  Created by Nikolay Fedotenko on 24.05.2021.
//

import SwiftUI
import BigNum

struct ContentView: View {
    @State var a: Double = 0.3
    @State var U: Double = 13.7
    @State var isLow = true
    @State var terms = [Double]()
    
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    
    let e = BigFloat(1.60217733e-19)
    let energy = BigFloat(2.194982e-18)
    
    let function: (_ x: Double, _ a: Double, _ U: Double) -> Double = { x, a, U in
        return abs(x) < a ? -U : 0
    }
    
    let oscillatorFunction: (_ x: Double, _ ω: Double) -> Double = { x, ω in
        return 0.5 * pow(ω, 2) * pow(x, 2)
    }
    
    var body: some View {
        VStack {
            Text("Витязев, Кукулиди, Федотенко, Шевченко (M32122)")
            Spacer()
            HStack {
                Chart(function: function, oscillatorFunction: oscillatorFunction, a: $a, U: $U)
                
                VStack {
                    Term(e: e, terms: $terms, U: $U, a: $a, isLow: $isLow)
                    
                    HStack {
                        Toggle("Низкая графика", isOn: $isLow)
                    }
                }
            }
            
            Text("Связанные состояния:")
            Text(terms[safe: 0] == nil ? "" : String(format: "%.1f", terms[0]))
            Text(terms[safe: 1] == nil ? "" : String(format: "%.1f", terms[1]))
            Text(terms[safe: 2] == nil ? "" : String(format: "%.1f", terms[2]))
            
            Spacer()
            
            Slider(value: $a, in: 0.1...0.5, step: 0.1, minimumValueLabel: Text("0.1"), maximumValueLabel: Text("0.5")) {
                Text("Ширина потенциальной ямы")
                    .font(.title)
            }
            
            Slider(value: $U, in: Double(energy / e)...2 * Double(energy / e), step: 0.5, minimumValueLabel: Text("13.7"), maximumValueLabel: Text("27.2")) {
                Text("Потенциальная энергия частицы, эВ")
                    .font(.title)
            }
        }
        .padding()
        .frame(maxWidth: .infinity, maxHeight: .infinity)
        .onAppear {
            
        }
    }
}

struct Chart: View {
    var function: (Double, Double, Double) -> Double
    var oscillatorFunction: (Double, Double) -> Double
    
    @Binding var a: Double
    @Binding var U: Double
    
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    
    var firstOscillatorOwnFunction: (Double) -> Double = { x in
        return pow(2.718281828, -0.5 * pow(x, 2))
    }
    
    var secondOscillatorOwnFunction: (Double) -> Double = { x in
        return x * pow(2.718281828, -0.5 * pow(x, 2))
    }
    
    var body: some View {
        let style = ChartStyle(backgroundColor: colorScheme == .dark ? Color.black : Color.white,
                               accentColor: .red,
                               secondGradientColor: .red,
                               textColor: .primary,
                               legendTextColor: .gray,
                               dropShadowColor: .gray)
        style.darkModeStyle = style
        
        let leftBorder: Double = -1
        let rightBorder: Double = 1
        var points = [Double]()
        var oscillatorPoints = [Double]()
        var firstOscillatorPoints = [Double]()
        var secondOscillatorPoints = [Double]()
        var energy = [Double]()
        
        for x in stride(from: leftBorder, to: rightBorder, by: 0.01) {
            points.append(function(x, a, U))
            
            let ω = pow(200 / U, 1 / 3) / (0.65 * a)
            let oscillatorPoint = oscillatorFunction(x, ω) - U
            
            oscillatorPoints.append(oscillatorPoint > 0 ? 0 : oscillatorPoint)
            
            firstOscillatorPoints.append(firstOscillatorOwnFunction(3 * x) / (a * 2) - U / 1.2)
            secondOscillatorPoints.append(secondOscillatorOwnFunction(3 * x) / (a * 2) - U / 3)
            energy.append(-U + 13.6)
        }
        
        return MultiLineChartView(data: [
            (oscillatorPoints, GradientColor(start: .blue, end: .blue)),
            (firstOscillatorPoints, GradientColor(start: .orange, end: .orange)),
            (secondOscillatorPoints, GradientColor(start: .orange, end: .orange)),
            (energy, GradientColor(start: .green, end: .green)),
            (points, GradientColor(start: .red, end: .red)),
        ],
        title: "Потенциальная яма",
        form: ChartForm.extraLarge)
    }
}

struct Term: View {
    
    let m = BigFloat(9.1093837015e-31)
    
    let ħ = BigFloat(1.054571817e-34)
    let π = BigFloat(3.1415926535897932384626)
    
    var e: BigFloat
    
    @Binding var terms: [Double]
    @Binding var U: Double
    @Binding var a: Double
    @Binding var isLow: Bool
    
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    
    var body: some View {
        var terms = [Double]()
        let style = ChartStyle(backgroundColor: colorScheme == .dark ? Color.black : Color.white,
                               accentColor: .red,
                               secondGradientColor: .red,
                               textColor: .primary,
                               legendTextColor: .gray,
                               dropShadowColor: .gray)
        
        let numberOfCurvedLines = 3
        
        style.darkModeStyle = style
        let scale = BigFloat(1e28)
        let kmax = BigFloat(1) / ħ * sqrt(BigFloat(2) * m * (BigFloat(U) / e)) / scale
        
        let leftBorder: Double = 0
        let rightBorder: Double = Double(kmax)
        var strightLinePoints = [Double]()
        var curvedLinesPoints = [[Double]](repeating: [], count: numberOfCurvedLines)
        
        var previousTerm = -1.0
        for x in stride(from: leftBorder, to: rightBorder, by: isLow ? 5 : 0.1) {
            let strightPoint = x * a
            strightLinePoints.append(strightPoint)
            
            for n in 0..<numberOfCurvedLines {
                let left = Double(π * BigFloat(n + 1))
                let rightTop = ħ * BigFloat(x) * scale
                let rightBottom = sqrt(BigFloat(2) * m * BigFloat(U) / e)
                let right = Double(rightTop / rightBottom)
                let point = left - 2 * asin(right)
                
                if abs(strightPoint - point) < (isLow ? 1 : 0.07) && abs(previousTerm - x) > 2 {
                    previousTerm = x
                    terms.append(x)
                }
                
                curvedLinesPoints[n].append(point)
            }
        }
        
        return MultiLineChartView(data: [(strightLinePoints, GradientColor(start: .red, end: .red))] + curvedLinesPoints.map { ($0, GradientColor(start: .blue, end: .blue)) },
                                  title: "Энергетический спектр",
                                  form: ChartForm.extraLarge)
            .onAppear {
                self.terms = terms
            }
            .onChange(of: terms) { value in
                self.terms = value
            }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
            .environment(\.sizeCategory, .large)
            .frame(width: 800, height: 500)
    }
}

extension Collection {
    subscript(safe index: Index) -> Element? {
        index >= startIndex && index < endIndex ? self[index] : nil
    }
}

