---
title: "Legea lui Benford"
author: "Daniel Mihai Baciu, Vlad George Mihai, Radu Stefan Rotaru"
date: "01/27/2022"
output: html_document
---

## Descriere

**Benford's Law**, also known as the Newcomb–Benford law, the law of anomalous numbers, or the first-digit law, is an observation that in many real-life sets of numerical data, the leading digit is likely to be small. In sets that obey the law, the number 1 appears as the leading significant digit about 30% of the time, while 9 appears as the leading significant digit less than 5% of the time. If the digits were distributed uniformly, they would each occur about 11,1% of the time. Benford's law also makes predictions about the distribution of second digits, third digits, digit combinations, and so on.

The graph to the right shows Benford's law for base 10, one of infinitely many cases of a generalized law regarding numbers expressed in arbitrary (integer) bases, which rules out the possibility that the phenomenon might be an artifact of the base 10 number system. Further generalizations were published in 1995 including analogous statements for both the nth leading digit as well as the joint distribution of the leading n digits, the latter of which leads to a corollary wherein the significant digits are shown to be a statistically dependent quantity.

It has been shown that this result applies to a wide variety of data sets, including electricity bills, street addresses, stock prices, house prices, population numbers, death rates, lengths of rivers, and physical and mathematical constants. Like other general principles about natural data—for example the fact that many data sets are well approximated by a normal distribution—there are illustrative examples and explanations that cover many of the cases where Benford's law applies, though there are many other cases where Benford's law applies that resist a simple explanation. It tends to be most accurate when values are distributed across multiple orders of magnitude, especially if the process generating the numbers is described by a power law (which is common in nature).

The law is named after physicist Frank Benford, who stated it in 1938 in a paper titled "The Law of Anomalous Numbers", although it had been previously stated by Simon Newcomb in 1881.

The law is similar in concept, though not identical in distribution, to Zipf's law.

$P(d)=lg(1+\frac{1}{d})\ $\


## Despre Aplicatia noastra

Aplicația noastră ilustrează corectitudinea Legii lui Benford pe **trei seturi de date** dupa cum urmeaza :

  1. [Covid](#unu) \
  2. [Populatia din USA](#doi) \
  5. [Șirul lui Fibonacci](#trei) \
  
### Date despre COVID ^[https://github.com/owid/covid-19-data/tree/master/public/data] {#unu}

**Primul set de date** cuprinde informații despre numărul de morți și numărul de infectari COVID. Datele le-am luat pe continente

#### Imbolnaviri 2020

![](img/WorldCases.png)

#### Morți 2020 - aici, pe acest caz, nu am putut evidentia legea lui Benford

![](img/AustraliaDeaths.png)

### Populatia din USA ^[https://www2.census.gov/programs-surveys/popest/datasets/] {#doi}

**Al doilea set de date** cuprinde informații despre populația din SUA din fiecare oras.

![](img/US_Census.png)

### Șirul lui Fibonacci ^[https://www.kaggle.com/brandonconrady/fibonacci-sequence-first-10001-numbers]{#trei}

**Al treilea set de date** cuprinde informații despre populația din SUA. Am ales acest set de date observând faptul că datele din acest tabel respectă condițiile Legii lui Benford. Interfața permite utilizatorului să afișeze pentru numerele din șirul lui Fibonacci atât graficul obținut prin calcularea procentului de frecvență al unei cifre alături de curba lui Benford, cât și graficul pentru procentul de frecvență al primelor două cifre, cât și curba generată în cazul respectării Legii lui Benford. Aceste date au dus la obținerea următorului grafic:

![](img/Fibo.png)

## Implementarea Aplicatiei

Pentru implementarea aplicației noastre am folosit următoarele pachete din R:

- `library("ggplot2")`
- `library("shiny")`

Respectând structura unei aplicații Shiny, codul nostru este împărțit în 3 mari componente:

  1. [Interfața Utilizatorului (UI)](#ui) \
  2. [Server](#srv) \
  3. [ShinyApp](#shiny) \

### Interfața Utilizatorului (UI): {#ui}

```R
    ui <- fluidPage(
  navbarPage("aplicatie",
             # h1("Aplicatie Shiny Legea lui Benford"),
             tabPanel("Despre aplicatie",p("Benford's law, also known as the Newcomb–Benford law, the law of anomalous numbers, or the first-digit law, is an observation that in many real-life sets of numerical data, the leading digit is likely to be small.[1] In sets that obey the law, the number 1 appears as the leading significant digit about 30 % of the time, while 9 appears as the leading significant digit less than 5 % of the time. If the digits were distributed uniformly, they would each occur about 11.1 % of the time.[2] Benford's law also makes predictions about the distribution of second digits, third digits, digit combinations, and so on.

The graph to the right shows Benford's law for base 10, one of infinitely many cases of a generalized law regarding numbers expressed in arbitrary (integer) bases, which rules out the possibility that the phenomenon might be an artifact of the base 10 number system. Further generalizations were published in 1995[3] including analogous statements for both the nth leading digit as well as the joint distribution of the leading n digits, the latter of which leads to a corollary wherein the significant digits are shown to be a statistically dependent quantity.

It has been shown that this result applies to a wide variety of data sets, including electricity bills, street addresses, stock prices, house prices, population numbers, death rates, lengths of rivers, and physical and mathematical constants.[4] Like other general principles about natural data—for example the fact that many data sets are well approximated by a normal distribution—there are illustrative examples and explanations that cover many of the cases where Benford's law applies, though there are many other cases where Benford's law applies that resist a simple explanation.[5][6] It tends to be most accurate when values are distributed across multiple orders of magnitude, especially if the process generating the numbers is described by a power law (which is common in nature).

The law is named after physicist Frank Benford, who stated it in 1938 in a paper titled <<The Law of Anomalous Numbers>>,[7] although it had been previously stated by Simon Newcomb in 1881.[8][9]

The law is similar in concept, though not identical in distribution, to Zipf's law.")),
             #div(includeMarkdown("info.rmd")
             tabPanel("Benford pe date Covid",
                      h4("Date incluse: 22-01-2020  ->  25.01.2022"),
                      h4("Efectul Covid asupra continentelor"),
                      p("In timpul pandemiei de COVID-19, oamenii ezita sa creada ca toate datele raportate in legatura 
                            cu numarul de cazuri sunt complete si corecte. De aceea un prim pas natural ar fi sa vedem daca
                            aceste date urmeaza legea lui Benford"),
                      p("Data set-urile pentru COVID-19 tind sa fie potrivite pentru legea lui Benford. Acestea includ 
                            numeroase categorii cu date zilnice din toata lumea."),
                      
                      sidebarLayout(
                        sidebarPanel(
                          radioButtons("tipNr", "Alege numaratoarea",
                                       choiceName = c('Numarul de infectari',
                                                      'Numarul de decese'),
                                       choiceValues = c('infectari',
                                                        'decese')
                          ),
                          selectInput("tipData", "Alege Tara/Continentul",
                                      choices = c('Africa',
                                                  'Australia',
                                                  'Asia',
                                                  'Europe',
                                                  'North America',
                                                  'South America',
                                                  'World'
                                      )),
                          sliderInput(inputId = "nrZile",
                                      label = "Numarul de zile din pandemie trecute",
                                      min = 1,
                                      max = 734,
                                      value = 200
                          )
                        ),
                        mainPanel(
                          tabsetPanel(
                            tabPanel("Graficul legii Benford pe acest set de date", plotOutput("date")),
                            tabPanel("Datele tabelului dorit", DT::dataTableOutput("covidTabel"))
                          )
                        )
                      )
             ),
             tabPanel("Benford pe populatie",
                      h4("Date incluse: 2020"),
                      h4("Date preluate din USA"),
                      
                      sidebarLayout(
                        sidebarPanel(
                          sliderInput(inputId = "usCensus",
                                      label = "Numarul de orase pe care se face studiul",
                                      min = 1,
                                      max = 81416,
                                      value = 1000
                          )
                        ),
                        mainPanel(
                          tabsetPanel(
                            tabPanel("Graficul legii Benford pe acest set de date", plotOutput("dateCensus")),
                            tabPanel("Datele tabelului dorit", DT::dataTableOutput("censusTabel"))
                          )
                        )
                      )
             ),
             tabPanel("Benford pe sirul Fibonacci",
                      h4("exemplul clasic de Benford"),
                      
                      sidebarLayout(
                        sidebarPanel(h4("Fibonacci"),
                                     sliderInput(inputId = "nrFibo",
                                                 label = "Numarul de entry-uri fibo",
                                                 min = 1,
                                                 max = 4000,
                                                 value = 200
                                     )
                        ),
                        mainPanel(
                          tabsetPanel(
                            tabPanel("Graficul legii Benford pe acest set de date", plotOutput("dateFibo")),
                            tabPanel("Datele tabelului dorit", DT::dataTableOutput("fiboTabel"))
                          )
                        )
                      )
             )
  ),
)

```

### Server: {#srv}

```R
    #partea de server-side
server <- function(session, input, output) {
  calculBenford <- function(r, days) {
    
    percent <- c(0 ,0, 0, 0, 0, 0, 0, 0, 0)
    freq <- c(0 ,0, 0, 0, 0, 0, 0, 0, 0)
    benfordV <- c(0 ,0, 0, 0, 0, 0, 0, 0, 0)
    
    firstDigit<-function(x) as.numeric(substr(gsub('[0.]', '', x), 1, 1))
    for(i in 1:days) {
      # num <- extract.digits(r, number.of.digits = 1)
      num<-firstDigit(r[i])
      freq[num] <- freq[num] + 1
    }
    
    sumTotal <- sum(freq)
    
    for (i in 1:9) {
      percent[i] <- freq[i] / sumTotal
    }
    
    for( i in 1:9) {
      benfordV[i] <- log10(1 + 1 / i)
    }
    
    dataFrame <- data.frame (
      nums = c("1", "2", "3", "4", "5", "6", "7", "8", "9"),
      benford = benfordV,
      percentages = percent
    )
    
    ggplot(data = dataFrame, aes(x = nums, group = 1)) + geom_bar(aes(y = percentages), stat = "identity", color = "blue", fill = "green") + geom_line(aes(y = benford), stat = "identity", color = "purple")
    
  }
  
  output$date <- renderPlot ({
    
    fileName <- paste(input$tipData, ".csv", sep = "")
    dataT <- (read.csv(fileName, header = TRUE))
    
    covid <- data.frame(
      # Continent = dataT$Continent,
      # Data = dataT$Date,
      Cazuri = dataT$Total_cases,
      Decese = dataT$Total_deaths
    )
    
    output$covidTabel = DT::renderDataTable({covid})
    
    nrType <-input$tipNr
    
    if(nrType == 'infectari')
      r <- dataT$Total_cases
    if(nrType == 'decese')
      r <- dataT$Total_deaths
    
    days <- input$nrZile
    
    calculBenford(r, days)
  })
  
  output$dateFibo <- renderPlot({
    fiboFile <- (read.csv("fibo.csv", header = TRUE))
    
    valFibo <- fiboFile$Value
    
    
    fibo <- data.frame(
      Index = fiboFile$Iteration,
      Value = fiboFile$Value
    )
    
    output$fiboTabel = DT::renderDataTable({fibo})
    calculBenford(valFibo, input$nrFibo)
  })
  
  output$dateCensus <- renderPlot({
    censusFile <- (read.csv("US_Census.csv", header = TRUE))
    
    valCensus <- censusFile$Population
    
    censUS <- data.frame(
      Population = censusFile$Population
    )
    
    output$censusTabel = DT::renderDataTable({censUS})
    
    calculBenford(valCensus, input$usCensus)
  })
  
}
```

### ShinyApp: {#shiny}

Pentru a putea rula aplicația noastră, avem nevoie de următoarea instrucțiune:

```R
    shinyApp(ui = ui, server = server)
```

