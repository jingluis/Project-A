#IMPORTANT: you need to set working directory to source file location
#if you use RStudio: go to Session -> Set Working Directory -> To Source File Location

#GNP relation between probability p and probability of the network being connected

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^gnp_opt1_.*\\.txt$")
colo = vector()
i = 0
leg = vector()
inici = c(10,50,100,250,500,1000)
for (val in list_of_files){
  result = paste("./", val, sep = "")
  leg = c(leg, paste("N = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(dades$V1,dades$V2,type = "l",lty = 2,ylim = c(0,1.0), lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Transmission Probability P")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+
}


legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)


#RGG relation between radius r and probability of the network being connected

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^rgg_opt1_.*\\.txt$")
colo = vector()
i = 0
leg = vector()
inici = c(10,50,100,250,500,1000)
for (val in list_of_files){
  result = paste("./", val, sep = "")
  leg = c(leg, paste("N = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(dades$V1,dades$V2,type = "l",lty = 2,ylim = c(0,1.0), lwd = 2,col = colors()[value],ylab = "Probability that network is connected", xlab = "Transmission Radius R")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}


legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)


#GNP relation between probability p and number of waiting connected components

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "gnp_opt2_.*\\.txt$")
colo = vector()
i = 0
leg = vector()
inici = c(10,50,100,250,500,1000)
for (val in 1:6){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("N = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(dades$V1,dades$V2,type = "l",lty = 6,lwd = 2,col = colors()[value],ylab = "Waiting number of Connected Components", xlab = "Transmission Probability P")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}


legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)


#RGG relation between radius r and number of waiting connected components


list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^rgg_opt2_.*\\.txt$")
colo = vector()
i = 0
leg = vector()
inici = c(10,50,100,250,500,1000)
for (val in 1:6){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("N = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(dades$V1,dades$V2,type = "l",lty = 2, lwd = 2,col = colors()[value],ylab = "Waiting number of Connected Components", xlab = "Transmission Radius R")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}



legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)


#GNP relation between probability p and the waiting maximum connected components size

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "gnp_opt4_.*\\.txt$")
colo = vector()
i = 0
leg = vector()
inici = c(10,50,100,250,500,1000)
for (val in 1:6){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("N = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0){
    plot(dades$V1,dades$V2,type = "l",ylim = c(0,1000),lty = 6,lwd = 2,col = colors()[value],ylab = "Waiting maximum connected component size", xlab = "Transmission Probability P")
    axis(side = 1, at = seq(0,1,by = 0.1))
  }
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}


legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)


#RGG relation between radius r and the waiting maximum connected component size


list_of_files <- list.files(path = "./", recursive = TRUE, patter = "^rgg_opt4_.*\\.txt$")
colo = vector()
i = 0
leg = vector()
inici = c(10,50,100,250,500,1000)
for (val in 1:6){
  result = paste("./", list_of_files[val], sep = "")
  leg = c(leg, paste("N = ", paste0(inici[i+1]),sep = "")) 
  dades <- read.table(result)
  value = floor(runif(1, min=1, max=657))
  colo = c(colo, colors()[value])
  if(i == 0) plot(dades$V1,dades$V2,type = "l",lty = 2,ylim = c(0,1000), lwd = 2,col = colors()[value],ylab = "Maximum connected component size", xlab = "Transmission Radius R")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6)  
  i = i+1
}



legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)





