#IMPORTANT: you need to set working directory to source file location
#if you use RStudio: go to Session -> Set Working Directory -> To Source File Location

#N = 10

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^10 .*\\.txt$")

colo = vector()
i = 0
leg = vector()
inici = c(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1)
for (val in 11:1){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("P = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(main = "N = 10",dades$V1,dades$V2,type = "l",lty = 2, ylim = c(0,1.0), lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Number of edges")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}

legend("topright", legend = leg, col = colo, lty = 2, cex = 0.75)


#N = 50

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^50 .*\\.txt$")

colo = vector()
i = 0
leg = vector()
inici = c(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1)
for (val in 11:1){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("P = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(main = "N = 50",dades$V1,dades$V2,type = "l",lty = 2,ylim = c(0,1.0), lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Number of edges")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}

legend("topright", legend = leg, col = colo, lty = 2, cex = 0.75)


#N = 100

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^100 .*\\.txt$")

colo = vector()
i = 0
leg = vector()
inici = c(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1)
for (val in 11:1){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("P = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(main = "N = 100",dades$V1,dades$V2,type = "l",lty = 2, ylim = c(0,1.0),lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Number of edges")
  
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}

legend("topright", legend = leg, col = colo, lty = 2, cex = 0.75)


#N = 250
list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^250 .*\\.txt$")

colo = vector()
i = 0
leg = vector()
inici = c(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1)
for (val in 11:1){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("P = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(main = "N = 250",dades$V1,dades$V2,type = "l",lty = 2, ylim = c(0,1.0),lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Number of edges")
  
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}

legend("topright", legend = leg, col = colo, lty = 2, cex = 0.75)

#N = 500
list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^500 .*\\.txt$")

colo = vector()
i = 0
leg = vector()
inici = c(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1)
for (val in 11:1){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("P = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(main = "N = 500",dades$V1,dades$V2,type = "l",lty = 2, ylim = c(0,1.0),lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Number of edges")
  
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}

legend("topright", legend = leg, col = colo, lty = 2, cex = 0.75)


#N = 1000
list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^1000 .*\\.txt$")

colo = vector()
i = 0
leg = vector()
inici = c(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1)
for (val in 11:1){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("P = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(main = "N = 1000",dades$V1,dades$V2,type = "l",lty = 2, ylim = c(0,1.0),lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Number of edges")
  
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}

legend("topright", legend = leg, col = colo, lty = 2, cex = 0.75)
