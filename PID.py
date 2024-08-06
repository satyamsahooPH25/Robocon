import time


class PID:
    
    def __init__(self,kp,ki,kd,centre_x):
        '''Sets the value for kp,ki and kd, along with the centre (The position we are trying to achieve)'''
        self.integ = 0;#Integration
        self.prop  = 0 #Proportional
        self.deriv = 0 #Derivative

        #kp ki and kd

        self.kp = kp
        self.ki = ki
        self.kd = kd

        #The time when the PID was last updated
        self.last_update = time.time()

        self.centre = centre_x

    #Restarts the PID (Useful when PID has been inactive and we need to again start using it)
    def restart(self):
        self.integ = 0;#Integration
        self.prop  = 0 #Proportional
        self.deriv = 0 #Derivative
        self.last_update = time.time()

        self.prev_error = 0
    
    def getError(self,curr_x):
        return curr_x-self.centre


    def update(self,error):
        
        #Get current time
        time_now = time.time()

        #Get the error (Prop)
        self.prop = error

        #Delta time with
        delta = time_now-self.last_update
        #A constant to prevent division by 0
        kappa = 0.0001

        #Get the integration
        self.integ += error*(delta)

        #Get the differentiation
        self.deriv = (error-self.prev_error)/(delta+kappa)

        #Update the last_update time
        self.last_update = time_now

        #Update previous error
        self.prev_error = error

    #Get the PID value
    def getPID(self):
        ''' Args:- Nothing(Must be updated before for it to work properly)
            
            Returns:- The PID Value (kp*prop + kd*deriv + ki*intgral)
        '''
        return self.kp*self.prop + self.kd*self.deriv+self.ki*self.integ
    
    #Combining functions to get a value
    def run(self,curr_x):
        ''' Args:- current_x of the largest ball
            Returns:- PID value'''
        

        #Get the error
        error = self.getError(curr_x)
        #Use the error to update PID
        self.update(error)
        #Return the PID value
        return self.getPID()

    