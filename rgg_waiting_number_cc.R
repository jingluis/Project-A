#IMPORTANT: you need to set working directory to source file location
#if you use RStudio: go to Session -> Set Working Directory -> To Source File Location

list_of_files <- list.files(path = "./", recursive = TRUE, patter = "\\.txt$")
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
  if(i == 0) plot(dades$V1,dades$V2,type = "l",lty = 2, lwd = 2,col = colors()[value],ylab = "Waiting number of Connected Components", xlab = "Transmission Radius R")
  else lines(dades$V1,dades$V2, col = colors()[floor(runif(1, min=1, max=657))], lwd = 2, type = "l", lty = 6) 
  i = i+1
}

leg = c(leg,"N = 100");
colo = c(colo,colo_for_100)

legend("bottomright", legend = leg, col = colo, lty = 2, cex = 1)
