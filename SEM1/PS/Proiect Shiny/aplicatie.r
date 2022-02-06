#Rotaru Radu-Stefan, Baciu Daniel, Mihai Vlad-George
#Grupa 243
#Facultatea de Matematica si Informatica
#Proiect Probabilitati si Statistica
#Legea lui Benford

#import-urile librariilor folosite pentru proiect
library(ggplot2)
library(shiny)
library(knitr)
library(shinythemes)

rmdfiles <- c("raport.Rmd")
sapply(rmdfiles, knit, quiet = T)

#aplicatia shiny
#partea de user interface
ui <- fluidPage(theme = shinytheme("darkly"),
  navbarPage("Benford's Law 243 PS",
             # h1("Aplicatie Shiny Legea lui Benford"),
             tabPanel("Despre aplicatie",
             withMathJax(includeMarkdown("raport.Rmd"))),
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
                      h4("Sirul Fibonacci este exemplul clasic de Benford."),
                      
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

shinyApp(ui = ui, server = server)
